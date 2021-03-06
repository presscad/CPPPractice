#ifndef INTERVIEW_H
#define INTERVIEW_H

#include <vector>
#include <string>
#include <sstream>

typedef std::vector<std::string> StringVector;

//What is the name of the "-->" operator?
void printNumbers();

/*
 *Why is processing a sorted array faster than an unsorted array?
 *Failing branch prediction is bad, a memory load after a branch prediction fail is just horrible!
 *A general rule of thumb is to avoid data-dependent branching in critical loops.
 *The performance of an if-statement depends on whether its condition has a predictable pattern.
   If the condition is always true or always false, the branch prediction logic in the processor
   will pick up the pattern. On the other hand, if the pattern is unpredictable, the if-statement
   will be much more expensive.
 *A branch predictor is a digital circuit that tries to guess which way a branch (e.g. an
   if-then-else structure) will go before this is known for sure.
*/
void sortedArrayVSUsorted();

/*
 *Why is one loop so much slower than two loops?
 *In the first two tests, the arrays are allocated separately.
 *In the second two tests, the arrays are packed together to break that alignment.
 *It caused by data alignment of the four pointers. This will cause some level of cache bank/way conflicts.
 *It does in fact look like it is allocating all the arrays separately. Usually when such large allocations
  are requested, the allocator will request fresh pages from the OS. Therefore, there is a high chance that
  large allocations will appear at the same offset from a page-boundary.
 *There is very likely possibility that this alignment causes false aliasing in the load/store units or
  the cache.
 *
 */
void oneLoopVSTwoLoops();

/*
 *Why does changing 0.1f to 0 slow down performance by 10x?
 *When denormal values are entirely computed in hardware, implementation techniques exist to allow
  their processing at speeds comparable to normal numbers;
  however, the speed of computation is significantly reduced on many modern processors;
  in extreme cases, instructions involving denormal operands may run as much as 100 times slower.
 */
void denormalFloatVSNormalFloat();

//Split string  elegently just use STL.
StringVector& splitString(const std::string &s, char delim, StringVector &elems);

//Trim string.
std::string startTrim(std::string&);
std::string endTrim(std::string&);

//Convert to string function template;
template <typename T>
std::string number2String ( T n )
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

//Best way to detect integer overflow in C/C++
size_t highestBitPosition(unsigned int);
bool addSafe(unsigned int,unsigned int);
bool multiplySafe(unsigned int,unsigned int);
bool exponentSafe(unsigned int,unsigned int);

//Appending a vector to a vector
template <typename T>
void mergeVector(std::vector<T>& a, const std::vector<T> &b)
{
	a.insert(a.end(), b.begin(), b.end());
}

//Most effective way for float and double comparison
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
	// the machine epsilon has to be scaled to the magnitude of the values used
	// and multiplied by the desired precision in ULPs (units in the last place)
	return std::abs(x - y) < std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<T>::min();
}
#endif // INTERVIEW_H
