#ifndef INTERVIEW_H
#define INTERVIEW_H

#include <vector>

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




#endif // INTERVIEW_H
