import os
import ctypes
import requests

SPI_SETDESKWALLPAPER = 20 
src = 'https://source.unsplash.com/random/1920x1080'

r = requests.head(src, allow_redirects=True)
print("Source: " + r.url)

with open('temp.jpg', 'wb') as handle:
        response = requests.get(src, stream=True)
        if not response.ok:
            print(response)
        for block in response.iter_content(1024):
            if not block:
                break
            handle.write(block)

path = os.getcwd() + "\\temp.jpg"

try:
	ctypes.windll.user32.SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, path , 3)
	print("Wallpaper set!")
	os.remove(path)
	print("Removed temp file")
except Exception as e:
	print("Some error occurred")
	print(e)

#https://stackoverflow.com/questions/1977694/how-can-i-change-my-desktop-background-with-python
#https://stackoverflow.com/questions/29425378/how-to-un-shorten-resolve-a-url-using-python-when-final-url-is-https
# https://stackoverflow.com/questions/30229231/python-save-image-from-url/30229298