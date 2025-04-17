import os
import qrcode

#img = qrcode.make("https://youtu.be/xvFZjo5PgG0")
img = qrcode.make("https://www.youtube.com/watch?v=4r7ApTfK7hg")
img.save("qrA.png", "PNG")