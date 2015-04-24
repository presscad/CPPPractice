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

#if statements
x = int(raw_input('Please enter an integer: '))
if x < 0:
	x = 0
	print 'Negative changed to zero'
elif x == 0:
	print 'Zero'
elif x == 1:
	print 'Single'
else:
	print 'More'

#for statements
words = ['cat', 'window', 'defenestrate']
for w in words:
	print w, len(w)

for w in words[:]:  # Loop over a slice copy of the entire list.
	if len(w) > 6:
		words.insert(0, w)
print words

#range() function
print range(10)
print range(5, 10)
print range(0, 10, 3)
print range(-10, -100, -30)

a = ['Mary', 'had', 'a', 'little', 'lamb']
for i in range(len(a)):
	print i, a[i]

for n in range(2, 10):
	for x in range(2, n):
		if n % x == 0:
			print n, 'equals', x, '*', n/x
			break
		else:
			# loop fell through without finding a factor
			print n, 'is a prime number'

#while True:
#	pass  # Busy-wait for keyboard interrupt (Ctrl+C)

def fib(n):    # write Fibonacci series up to n
	"""Print a Fibonacci series up to n."""
	a, b = 0, 1
	while a < n:
		print a,
		a, b = b, a+b
# Now call the function we just defined:
fib(2000)

def ask_ok(prompt, retries=4, complaint='Yes or no, please!'):
    while True:
        ok = raw_input(prompt)
        if ok in ('y', 'ye', 'yes'):
            return True
        if ok in ('n', 'no', 'nop', 'nope'):
            return False
        retries = retries - 1
        if retries < 0:
            raise IOError('refusenik user')
        print complaint

ask_ok('Do you really want to quit?')

def parrot(voltage, state='a stiff', action='voom', type='Norwegian Blue'):
    print voltage,state,action,type

parrot(1000)                                          # 1 positional argument
parrot(voltage=1000)                                  # 1 keyword argument
parrot(voltage=1000000, action='VOOOOOM')             # 2 keyword arguments
parrot(action='VOOOOOM', voltage=1000000)             # 2 keyword arguments
parrot('a million', 'bereft of life', 'jump')         # 3 positional arguments
parrot('a thousand', state='pushing up the daisies')  # 1 positional, 1 keyword

def cheeseshop(kind, *arguments, **keywords):
    print "-- Do you have any", kind, "?"
    print "-- I'm sorry, we're all out of", kind
    for arg in arguments:
        print arg
    print "-" * 40
    keys = sorted(keywords.keys())
    for kw in keys:
        print kw, ":", keywords[kw]

cheeseshop("Limburger", "It's very runny, sir.",
           "It's really very, VERY runny, sir.",
           shopkeeper='Michael Palin',
           client="John Cleese",
           sketch="Cheese Shop Sketch")

range(3, 6)             # normal call with separate arguments
args = [3, 6]
print range(*args)            # call with arguments unpacked from a list

def make_incrementor(n):
	return lambda x: x + n

f = make_incrementor(42)
print f(0)
print f(1)

pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
pairs.sort(key=lambda pair: pair[1])
print pairs

def my_function():
	"""Do nothing, but document it.

	No, really, it doesn't do anything.
	"""
	pass

print my_function.__doc__

#Coding Style:
#Use 4-space indentation, and no tabs.
#4 spaces are a good compromise between small indentation (allows greater nesting depth) and large indentation (easier to read). Tabs introduce confusion, and are best left out.
#Wrap lines so that they don’t exceed 79 characters.
#This helps users with small displays and makes it possible to have several code files side-by-side on larger displays.
#Use blank lines to separate functions and classes, and larger blocks of code inside functions.
#When possible, put comments on a line of their own.
#Use docstrings.
#Use spaces around operators and after commas, but not directly inside bracketing constructs: a = f(1, 2) + g(3, 4).
#Name your classes and functions consistently; the convention is to use CamelCase for classes and lower_case_with_underscores for functions and methods.
#Always use self as the name for the first method argument (see A First Look at Classes for more on classes and methods).
#Don’t use fancy encodings if your code is meant to be used in international environments. Plain ASCII works best in any case.

a = [66.25, 333, 333, 1, 1234.5]
print a.count(333), a.count(66.25), a.count('x')
a.insert(2, -1)
a.append(333)
print a
print a.index(333)
a.remove(333)
print a
a.reverse()
print a
a.sort()
print a
print a.pop()
print a

def f(x): return x % 3 == 0 or x % 5 == 0
print filter(f, range(2, 25))

def cube(x): return x*x*x
print map(cube, range(1, 11))

def add(x,y): return x+y
print reduce(add, range(1, 101))

from math import pi
print [str(round(pi, i)) for i in range(1, 6)]

matrix = [[1, 2, 3, 4],[5, 6, 7, 8],[9, 10, 11, 12]]
print [[row[i] for row in matrix] for i in range(4)]

a = [-1, 1, 66.25, 333, 333, 1234.5]
del a[0]
print a
del a[2:4]
print a
del a[:]
print a

t = 12345, 54321, 'hello!'
print t[0]
print t
# Tuples may be nested:
u = t, (1, 2, 3, 4, 5)
print u
# Tuples are immutable:
# but they can contain mutable objects:
v = ([1, 2, 3], [3, 2, 1])
print v

basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
fruit = set(basket)               # create a set without duplicates
print fruit
print 'orange' in fruit                 # fast membership testing
True
print 'crabgrass' in fruit
False

# Demonstrate set operations on unique letters from two words
a = set('abracadabra')
b = set('alacazam')
print a                                  # unique letters in a
print a - b                              # letters in a but not in b
print a | b                              # letters in either a or b
print a & b                              # letters in both a and b
print a ^ b                              # letters in a or b but not both

a = {x for x in 'abracadabra' if x not in 'abc'}
print a

tel = {'jack': 4098, 'sape': 4139}
tel['guido'] = 4127
print tel
print tel['jack']
del tel['sape']
tel['irv'] = 4127
print tel
print tel.keys()
print 'guido' in tel
True

#The dict() constructor builds dictionaries directly from sequences of key-value pairs:
print dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
print dict(sape=4139, guido=4127, jack=4098)

print {x: x**2 for x in (2, 4, 6)}

#When looping through a sequence, the position index and corresponding value can be retrieved at the same time using the enumerate() function.
for i, v in enumerate(['tic', 'tac', 'toe']):
	print i, v

#To loop over two or more sequences at the same time, the entries can be paired with the zip() function.
questions = ['name', 'quest', 'favorite color']
answers = ['lancelot', 'the holy grail', 'blue']
for q, a in zip(questions, answers):
	print 'What is your {0}?  It is {1}.'.format(q, a)

#To loop over a sequence in reverse, first specify the sequence in a forward direction and then call the reversed() function.
for i in reversed(xrange(1,10,2)):
	print i

#To loop over a sequence in sorted order, use the sorted() function which returns a new sorted list while leaving the source unaltered.
basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
for f in sorted(set(basket)):
	print f

#When looping through dictionaries, the key and corresponding value can be retrieved at the same time using the iteritems() method.
knights = {'gallahad': 'the pure', 'robin': 'the brave'}
for k, v in knights.iteritems():
	print k, v
	print f

import sys
#print sys.ps1
#print sys.ps2
#sys.ps1 = 'C> '

import sys
print sys.path

import fibo
print dir(fibo)
print dir(sys)

import __builtin__
dir(__builtin__)
print(1/7)

for x in range(1,11):
    print repr(x).rjust(2),repr(x*x).rjust(3),repr(x*x*x).rjust(4)

import math
print 'The value of PI is approximately {}.'.format(math.pi)

with open("test.txt","w") as f:
    f.write("Hello File!")

