# -*- coding: utf-8 -*-
"""
Created on Fri Oct  4 14:29:50 2019

@author: MALADAS
"""

import xml.etree.ElementTree as ET
import csv

#Open config xml
tree = ET.parse("sample_config.xml")
root = tree.getroot()

#Open structure of config
f= open("ax5043_config_str.txt","r")
regnames = f.readlines()

# open a file for writing reg values
reg_data = open('ax5043_regs.csv', 'w')
csvwriter = csv.writer(reg_data)

regs = []


for reg in regnames:
    try:
        value = root.find(reg.strip()).text
        regs.append(value)
    except:
        regs.append(0x00)
        
    
    
csvwriter.writerow(regs)    
reg_data.close()