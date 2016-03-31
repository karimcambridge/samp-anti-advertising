/*
	Copyright 2016 Kar

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

	stringContainsIP(const szStr[]);

	This include accurately detects if an IP is in a string.

	Created by Kar on Wednesday, March 30th, 2016.
*/

#if defined _INC_ANTI_ADVERTISING
	#endinput
#endif
#define _INC_ANTI_ADVERTISING

stock stringContainsIP(const szStr[])
{
	new 
		i = 0, ch, len = strlen(szStr), trueIPInts = 0, bool:isNumNegative = false, bool:numIsValid = true, // Invalid numbers are 1-1
		numberFound = -1, numLen = 0, numStr[4] // -225 (4 len)
	;
	while(i <= len)
	{
		ch = szStr[i];
		switch(ch)
		{
			case '0'..'9', '-': // store negatives (-1.-1.-1.-1)
			{
				if(numIsValid) {
					if(ch == '-') {
						if(numLen == 0) {
							isNumNegative = true;
						} else {
							numIsValid = false;
						}
					}
					if(numLen == (3 + _:isNumNegative)) { // IP Num is valid up to 4 characters.. -255
						for(numLen = 3; numLen > 0; numLen--) {
							numStr[numLen] = EOS;
						}
					} else {
						numStr[numLen++] = ch;
					}
				}
			}
			default: // skip non +/-0-255
			{
				if(numLen && numIsValid) {
					numberFound = strval(numStr);
					if(numberFound >= 0 && numberFound <= 255) {
						if(++trueIPInts >= 4) {
							break;
						}
					}
					//printf("numberFound: %d. numStr: %s. isNumNegative: %d", numberFound, numStr, isNumNegative);
					for(numLen = 3; numLen > 0; numLen--) { // strdel(numStr, 0, 3); // numStr[numLen] = EOS; ... they just won't work d:
						numStr[numLen] = EOS;
					} // numLen goes back to 0!
					isNumNegative = false;
				} else {
					numIsValid = true;
				}
			}
		}
		i++;
	}
	//printf("trueIPInts: %d", trueIPInts);
	return (trueIPInts >= 4);
}
