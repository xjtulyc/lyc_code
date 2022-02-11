#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 27 01:08:09 2021
Translator: cn to en
@author: Youcheng Li
"""
'''
load 3rd lib
'''
'''
Rely lib:
    -i https://pypi.douban.com/simple/    
    pip install pylangtools
    pip install jieba
    pip install keras
    pip install keras-transformer
    pip install tensorflow==1.15.5
'''
import sys
sys_path = 'c:/users/ai chyan/appdata/local/programs/python/python38/lib/site-packages'
sys.path.append(sys_path)
import numpy as np
import pickle
import operator
import pandas as pd
import jieba
from pylangtools.langconv import *
import tensorflow as tf
from tensorflow import keras
import keras_transformer
from keras_transformer import get_model, decode
from keras.models import load_model
from keras.models import model_from_yaml
from keras.preprocessing import sequence
import matplotlib.pyplot as plt
import matplotlib
import requests

def Traditional2Simplified(sentence):
    sentence = Converter('zh-hans').convert(sentence)
    return sentence
with open('cmn.txt', 'r', encoding='utf-8') as f:
    lines = f.read().split('\n');
    lines = lines[0:len(lines)-1]
source_tokens=[]
target_tokens=[]
for pos, line in enumerate(lines):
    line = line.split('\t')
    e = line[0][:-1] + " " + line[0][-1:]
    c = line[1]
    target_tokens.append(' '.join(e.split(' ')))
    source_tokens.append(' '.join(jieba.lcut(Traditional2Simplified(c).strip(), cut_all=False)))
#     source_tokens.append(' '.join(Traditional2Simplified(c).strip()))


# 生成不同语言的词典
def build_token_dict(token_list):
    token_dict = {
        '<PAD>': 0,
        '<START>': 1,
        '<END>': 2,
    }
    for line in token_list:
        for token in line.split(' '):
            if token not in token_dict:
                token_dict[token]=len(token_dict)
    return token_dict

source_token_dict = build_token_dict(source_tokens)
target_token_dict = build_token_dict(target_tokens)
target_token_dict_inv = {v: k for k, v in target_token_dict.items()}

# 添加特殊符号
encode_tokens = [['<START>'] + tokens.split(' ') + ['<END>'] for tokens in source_tokens]
decode_tokens = [['<START>'] + tokens.split(' ') + ['<END>'] for tokens in target_tokens]
output_tokens = [tokens.split(' ') + ['<END>', '<PAD>'] for tokens in target_tokens]

source_max_len = max(map(len, encode_tokens))
target_max_len = max(map(len, decode_tokens))



encode_tokens = [tokens + ['<PAD>'] * (source_max_len - len(tokens)) for tokens in encode_tokens]
decode_tokens = [tokens + ['<PAD>'] * (target_max_len - len(tokens)) for tokens in decode_tokens]
output_tokens = [tokens + ['<PAD>'] * (target_max_len - len(tokens)) for tokens in output_tokens]

encode_input = [list(map(lambda x: source_token_dict[x], tokens)) for tokens in encode_tokens]
decode_input = [list(map(lambda x: target_token_dict[x], tokens)) for tokens in decode_tokens]
decode_output = [list(map(lambda x: [target_token_dict[x]], tokens)) for tokens in output_tokens]

print('encode_input: ', len(encode_input))

path = 'middle_data/'
with open(path + 'encode_input.pkl', 'wb') as f:
    pickle.dump(encode_input, f, pickle.HIGHEST_PROTOCOL)
with open(path + 'decode_input.pkl', 'wb') as f:
    pickle.dump(decode_input, f, pickle.HIGHEST_PROTOCOL)
with open(path + 'decode_output.pkl', 'wb') as f:
    pickle.dump(decode_output, f, pickle.HIGHEST_PROTOCOL)
with open(path + 'source_token_dict.pkl', 'wb') as f:
    pickle.dump(source_token_dict, f, pickle.HIGHEST_PROTOCOL)
with open(path + 'target_token_dict.pkl', 'wb') as f:
    pickle.dump(target_token_dict, f, pickle.HIGHEST_PROTOCOL)
with open(path + 'source_tokens.pkl', 'wb') as f:
    pickle.dump(source_tokens, f, pickle.HIGHEST_PROTOCOL)

# %tensorflow_version 1.x
main_path = ''
path = 'middle_data/'
with open(path + 'encode_input.pkl', 'rb') as f:
    encode_input = pickle.load(f)
with open(path + 'decode_input.pkl', 'rb') as f:
    decode_input = pickle.load(f)
with open(path + 'decode_output.pkl', 'rb') as f:
    decode_output = pickle.load(f)
with open(path + 'source_token_dict.pkl', 'rb') as f:
    source_token_dict = pickle.load(f)
with open(path + 'target_token_dict.pkl', 'rb') as f:
    target_token_dict = pickle.load(f)
with open(path + 'source_tokens.pkl', 'rb') as f:
    source_tokens = pickle.load(f)
print('Done')


print(len(source_token_dict))
print(len(target_token_dict))
print(len(encode_input))
# 构建模型
model = keras_transformer.get_model(
    token_num=max(len(source_token_dict), len(target_token_dict)),
    embed_dim=64,
    encoder_num=2,
    decoder_num=2,
    head_num=4,
    hidden_dim=256,
    dropout_rate=0.05,
    use_same_embed=False,  # 不同语言需要使用不同的词嵌入
)
model.compile('adam', 'sparse_categorical_crossentropy')
# model.summary()
print('Done')

# #训练模型
# from keras.callbacks import ModelCheckpoint, ReduceLROnPlateau
# # filepath = "modles/W--{epoch:3d}-{loss:.4f}-.h5"
# filepath = "modles/"
# checkpoint = ModelCheckpoint(filepath,
#                     monitor='loss',
#                     verbose=1,
#                     save_best_only=True,
#                     mode='min',
#                     period=2,
#                     save_weights_only=True
#                     )
# reduce_lr = ReduceLROnPlateau(monitor='loss', 
#                     factor=0.2, 
#                     patience=2, 
#                     verbose=1, 
#                     mode='min', 
#                     min_delta=0.0001, 
#                     cooldown=0, 
#                     min_lr=0
#                     )
# callbacks_list = [checkpoint, reduce_lr]
# model.fit(
#     x=[np.array(encode_input[:20000]), np.array(decode_input[:20000])],
#     y=np.array(decode_output[:20000]),
#     epochs=100,
#     batch_size=64, 
#     verbose=1,
#     callbacks=callbacks_list, 
#     # class_weight=None, 
#     # max_queue_size=5, 
# #    workers=1, 
# #    use_multiprocessing=False,
#     # shuffle=False,
# #    initial_epoch=initial_epoch_
#     )
# model.save('modles/model.h5')

# #加载模型
model.load_weights('modles/model.h5')
target_token_dict_inv = {v: k for k, v in target_token_dict.items()}
print('Done')

def get_input(seq):
    seq = ' '.join(jieba.lcut(seq, cut_all=False))
    # seq = ' '.join(seq)
    seq = seq.split(' ')
    print(seq)
    seq = ['<START>'] + seq + ['<END>']
    seq = seq + ['<PAD>'] * (34 - len(seq))
    print(seq)
    for x in seq:
        try:
            source_token_dict[x]
        except KeyError:
            flag=False
            break
        else:
            flag=True
    if(flag):
        seq = [source_token_dict[x] for x in seq]
    return flag, seq
def get_ans(seq):
    decoded = decode(
    model,
    [seq],
    start_token=target_token_dict['<START>'],
    end_token=target_token_dict['<END>'],
    pad_token=target_token_dict['<PAD>'],
    # top_k=10,
    # temperature=1.0,
  )
    # print(' '.join(map(lambda x: target_token_dict_inv[x], decoded[0][1:-1])))
    return(' '.join(map(lambda x: target_token_dict_inv[x], decoded[0][1:-1])))
# while True:
    # seq = input()
    # if seq == 'x':
    #     break
    # flag, seq = get_input(seq)
    # if(flag):
    #     translate = get_ans(seq)
    # else:
    #     print('听不懂呢。')


with open('translate.txt','r') as f:
    translate = f.read()
seq = translate[0:len(translate)-1]
flag, seq = get_input(seq)
if(flag):
    translate = get_ans(seq)
    print(translate)# 这个是翻译的句子
else:
    translate = 'A woman sitting on a horse on a dirt field.'
    print('A woman sitting on a horse on a dirt field.')
with open('translate_en.txt','w+') as f:
    f.write(translate)
