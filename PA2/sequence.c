#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>

long *Generate_2p3q_Seq(int length, int *seq_size)
{
  //Determination of maximum number of elements sequence can have.
  int sequence_l = 0;
  long power_3 = 1;
  //Check until last element is greater than the length of array.
  while(power_3 < length){
    power_3 *= 3;
    ++sequence_l;
  }

  int sequence_size = sequence_l * (sequence_l + 1);
  
  long *sequence = (long *)malloc(sizeof(long) * sequence_size);
  
  if (sequence == NULL)
  {
    *seq_size = 0;
    return NULL;
  }

  //(Consider Changing Indexes)
  long previous_int_ind = -1;
  long next_int_ind = 0;
  long new_int = 1;
  power_3 = 3;

  //Generate Sequence in Order.
  while(new_int < length)
  {
    ++previous_int_ind; 
    sequence[previous_int_ind] = new_int;
    if (sequence[next_int_ind] * 2 > power_3)
    {
      new_int = power_3;
      power_3 *= 3;
    }
    else
    {
      new_int = sequence[next_int_ind] * 2;
      ++next_int_ind;
    }
  }

  *seq_size = ++previous_int_ind;

  return sequence;
}
