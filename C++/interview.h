#ifndef INTERVIEW_H
#define INTERVIEW_H

//What is the name of the “-->” operator?
void printNumbers();

/*
Why is processing a sorted array faster than an unsorted array?
(1)Failing branch prediction is bad, a memory load after a branch prediction fail is just horrible!
(2)A general rule of thumb is to avoid data-dependent branching in critical loops.
(3)The performance of an if-statement depends on whether its condition has a predictable pattern.
   If the condition is always true or always false, the branch prediction logic in the processor
   will pick up the pattern. On the other hand, if the pattern is unpredictable, the if-statement
   will be much more expensive.
(4)A branch predictor is a digital circuit that tries to guess which way a branch (e.g. an
   if-then-else structure) will go before this is known for sure.
*/
void sortedArrayVSUsorted();


#endif // INTERVIEW_H
