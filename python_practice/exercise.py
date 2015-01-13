# -*- coding: utf-8 -*-

currency = u"€"
print ord('a')

width = 20
height = 5 * 9
print width * height

tax = 12.5 / 100
price = 100.50
print price * tax
print round(price * tax, 2)

print 'spam eggs'  # single quotes
print "spam eggs"
print 'doesn\'t'  # use \' to escape the single quote...
print "doesn't"
print "doesn't"  # ...or use double quotes instead
print '"Yes," he said.'
print "\"Yes,\" he said."
print '"Isn\'t," she said.'
print 'C:\some\name'  # here \n means newline!
print r'C:\some\name'  # note the r before the quote
print """\
Usage: thingy [OPTIONS]
     -h                        Display this usage message
     -H hostname               Hostname to connect to
"""

print 3 * 'un' + 'ium'
print 'Py' 'thon'

prefix = 'Py'
print prefix + 'thon'

text = ('Put several strings within parentheses '
            'to have them joined together.')
print text			

word = 'Python'
print word[0]  # character in position 0
print word[5]  # character in position 5
print word[-1]  # last character
print word[-2]  # second-last character
print word[-6]

print word[0:2]  # characters from position 0 (included) to 2 (excluded)
print word[2:5]  # characters from position 2 (included) to 5 (excluded)

print word[:2] + word[2:]
print word[:4] + word[4:]

print word[:2]  # character from the beginning to position 2 (excluded)
print word[4:]  # characters from position 4 (included) to the end
print word[-2:] # characters from the second-last (included) to the end

#####remember how slices work############
# +---+---+---+---+---+---+
# | P | y | t | h | o | n |
# +---+---+---+---+---+---+
# 0   1   2   3   4   5   6
#-6  -5  -4  -3  -2  -1
#########################################

print word[4:42]
print word[42:]

s = 'supercalifragilisticexpialidocious'
print len(s)

print u'Hello World !'
print u'Hello\u0020World !'
print ur'Hello\u0020World !'
print ur'Hello\\u0020World !'

print u"abc"
print str(u"abc")
print u"äöü".encode('utf-8')

squares = [1, 4, 9, 16, 25]
print squares
print squares[0]  # indexing returns the item
print squares[-1]
print squares[-3:]  # slicing returns a new list
print squares[:]
print squares + [36, 49, 64, 81, 100]

cubes = [1, 8, 27, 65, 125]  # something's wrong here
cubes[3] = 64  # replace the wrong value
print cubes

cubes.append(216)  # add the cube of 6
cubes.append(7 ** 3)  # and the cube of 7
print cubes

letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
print letters
# replace some values
letters[2:5] = ['C', 'D', 'E']
print letters
# now remove them
letters[2:5] = []
print letters
# clear the list by replacing all the elements with an empty list
letters[:] = []
print letters

letters = ['a', 'b', 'c', 'd']
print len(letters)

a = ['a', 'b', 'c']
n = [1, 2, 3]
x = [a, n]
print x
print x[0]
print x[0][1]

# Fibonacci series:
# the sum of two elements defines the next
a, b = 0, 1
while b < 10:
	print b
	a, b = b, a+b

i = 256*256
print 'The value of i is', i





