printer_char = '\u2588'
full  =printer_char+printer_char+printer_char+printer_char+printer_char+printer_char+printer_char
first =printer_char+"      "
last  ="      "+printer_char
arrow =printer_char+"     "+printer_char


zero  =   [ full , arrow, arrow, arrow, arrow, arrow, arrow, arrow, full ]
one   =   [ last , last , last , last , last , last , last , last , last ]
two   =   [ full , last , last , last , full , first, first, first, full ]
three =   [ full , last , last , last , full , last , last , last , full ]
four  =   [ arrow, arrow, arrow, arrow, full , last , last , last , last ]
five  =   [ full , first, first, first, full , last , last , last , full ]
six   =   [ full , first, first, first, full , arrow, arrow, arrow, full ]
seven =   [ full , last , last , last , last , last , last , last , last ]
eight =   [ full , arrow, arrow, arrow, full , arrow, arrow, arrow, full ]
nine  =   [ full , arrow, arrow, arrow, full , last , last , last , full ]

digits = [zero,one,two,three,four,five,six,seven,eight,nine]

def draw_digits(numbers):
    length = len(numbers)
    line0,line1,line2,line3,line4,line5,line6,line7,line8='','','','','','','','',''
    
    for index in range(length):
        line0 += numbers[index][0] + '   '
        line1 += numbers[index][1] + '   '
        line2 += numbers[index][2] + '   '
        line3 += numbers[index][3] + '   '
        line4 += numbers[index][4] + '   '
        line5 += numbers[index][5] + '   '
        line6 += numbers[index][6] + '   '
        line7 += numbers[index][7] + '   '
        line8 += numbers[index][8] + '   '
        
    print(line0)
    print(line1)
    print(line2)
    print(line3)
    print(line4)
    print(line5)
    print(line6)
    print(line7)
    print(line8)


import random
import time
import subprocess as sp

# Clear the screen before staring the Prints
tmp = sp.call('clear', shell=True)

for i in range(4):
   rand_numbers = random.sample(range(10), 4)
   seven_seg_list = []
   for dig in rand_numbers:
      seven_seg_list.append(digits[dig])
   
   # Print a line before drawing the numbers
   print()
   draw_digits(seven_seg_list)
   time.sleep(5)
   tmp = sp.call('clear', shell=True)
