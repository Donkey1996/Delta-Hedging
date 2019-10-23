#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct 22 16:39:11 2019

@author: mengxiao
"""

import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt 
import matplotlib.pyplot as plt
from scipy import stats

data1 = pd.read_csv("result1.csv")
x= np.array(data1).T
sns.distplot(x, kde=False, fit=stats.gamma);


data2 = pd.read_csv("result2.csv")
data = [[0]*100]*100
for i in range(100):
	data[i] = [float(x) for x in data2.iloc[100*i+i:100*i+i+100,1]]


for i in range(100):
	plt.plot(range(100), data[i])