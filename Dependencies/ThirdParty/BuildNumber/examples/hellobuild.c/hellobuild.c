/* HelloBuild example

   See README.TXT for documentation of BuildNumber
   Licensed under the BSD license. See LICENSE.TXT for terms.
   
   BuildNumber (c) 2006 John M. Stoneham. All rights reserved.
*/

#include <stdio.h>

/* note that buildnumber.h does not have to exist before make
   is executed the first time, since it will be created before
   this file is compiled */
#include "buildnumber.h"

int main(int argc, char *argv[])
{

  printf("Hello Build " BUILDNUMBER_STR "!\n");
  printf("The next build will be Build %d.\n", (BUILDNUMBER + 1));
  
  return 0;

}
