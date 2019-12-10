import pyautogui
import urllib
import requests
import time as t
from PIL import Image
import pytesseract
import webbrowser
import re
#Taking screen shot of rectangular area of question
#Coordinates obtained from xdotool,FORMAT:region=(left,top,width,height)
im1 = pyautogui.screenshot(region=(1012,339,299,78))
im1.save('b.png')
im = Image.open('b.png')
#Black and white Converion
gray = im.convert('L')
bw = gray.point(lambda x: 0 if x<128 else 255, '1')
bw.save("result_bw.png")
im2=Image.open('result_bw.png')
#OCR
text = pytesseract.image_to_string(im2)
#Question Extraction
text2=text.split('?')
text3=text2[0]
print (text3)
#text4=text2[1]
#text5=text4.split('\n')
#print(text4)
q=text3.replace("\n"," ")
chrome_path='/usr/bin/chromium-browser %s'
url='https://www.google.co.in/search?q='+q
#url2='https://www.google.co.in/search?q='+text5[2]
#url3='https://www.google.co.in/search?q='+text5[4]
#url4='https://www.google.co.in/search?q='+text5[6]
webbrowser.get(chrome_path).open(url)
#webbrowser.get(chrome_path).open(url2)
# webbrowser.get(chrome_path).open(url3)
# webbrowser.get(chrome_path).open(url4)
