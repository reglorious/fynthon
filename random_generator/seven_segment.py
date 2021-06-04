import random
import time
import subprocess as sp

# The character that will be used to print the number on Console
printer_char = '\u2588'

# Spaces and lengths for Seven Segment Display
full  =printer_char+printer_char+printer_char+printer_char+printer_char+printer_char+printer_char
first =printer_char+"      "
last  ="      "+printer_char
arrow =printer_char+"     "+printer_char

# Seven Segment Layout for 0 to 9
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

# List of Digits
digits = [zero,one,two,three,four,five,six,seven,eight,nine]

# Seven Segment Digit Drawing Logic
# It draws one line per digit for all digits 
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
        
    # The prints below each draws one segment of the Seven Segment Display
    # There are totally 9 lines of charater, that makes one digit
    print(line0)
    print(line1)
    print(line2)
    print(line3)
    print(line4)
    print(line5)
    print(line6)
    print(line7)
    print(line8)



# Clear the screen before staring the Prints
tmp = sp.call('clear', shell=True)
# Size of the PIN
rand_length = 10
# Sleep times in seconds for new PIN generation
sleep_time = 20

for i in range(rand_length):
   rand_numbers = random.sample(range(10), rand_length)
   seven_seg_list = []
   for dig in rand_numbers:
      seven_seg_list.append(digits[dig])
   
   # Print a line before drawing the numbers
   print()
   draw_digits(seven_seg_list)
   time.sleep(sleep_time)
   tmp = sp.call('clear', shell=True)
