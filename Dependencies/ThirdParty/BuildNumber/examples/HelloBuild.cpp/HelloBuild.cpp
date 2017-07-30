/* HelloBuild C++ example

   See README.TXT for documentation of BuildNumber
   Licensed under the BSD license. See LICENSE.TXT for terms.
   
   BuildNumber (c) 2006 John M. Stoneham. All rights reserved.
*/

#include <iostream>

/* note that buildnumber.h does not have to exist before make
   is executed the first time, since it will be created before
   this file is compiled */
#include "buildnumber.h"

using namespace std;

int main(int argc, char *argv[])
{

  cout << "Hello Build " BUILDNUMBER_STR "!" << endl;
  cout << "The next build will be Build " << (BUILDNUMBER + 1) << endl;
  
  return 0;

}
