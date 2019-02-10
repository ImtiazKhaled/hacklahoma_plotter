import subprocess
from PIL import Image
import numpy as np
import os

filename, file_extension = os.path.splitext('C://Potrace/alpha.png')

if file_extension == ".jpg" or ".jpeg":

        img = Image.open('alpha.jpg')
        ary = np.array(img)

        # Split the three channels
        r, g, b = np.split(ary, 3, axis=2)
        r = r.reshape(-1)
        g = r.reshape(-1)
        b = r.reshape(-1)

        # Standard RGB to grayscale
        bitmap = list(map(lambda x: 0.299*x[0]+0.587*x[1]+0.114*x[2],
                          zip(r, g, b)))
        bitmap = np.array(bitmap).reshape([ary.shape[0], ary.shape[1]])
        bitmap = np.dot((bitmap > 128).astype(float), 255)
        im = Image.fromarray(bitmap.astype(np.uint8))
        im.save('alpha.bmp')
        
elif file_extension == ".png":

        file_in = "alpha.png"
        img = Image.open(file_in)
        file_out = "alpha.bmp"
        img.save(file_out)

else:
    print('File must be either png or jpg')


subprocess.call('potrace -s -o alpha.svg alpha.bmp', shell=True)
