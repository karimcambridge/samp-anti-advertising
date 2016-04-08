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

	stringContainsIP(const szStr[], bool:ignoreNegatives = false);

	This include accurately detects if an IP is in a string.

	Created by Kar on Wednesday, March 30th, 2016.
*/

#if defined _INC_ANTI_ADVERTISING
	#endinput
#endif
#define _INC_ANTI_ADVERTISING

stock stringContainsIP(const szStr[], bool:fixedSeparation = true, bool:ignoreNegatives = false)
{
	new 
		i = 0, ch, lastCh, len = strlen(szStr), trueIPInts = 0, bool:isNumNegative = false, bool:numIsValid = true, // Invalid numbers are 1-1
		numberFound = -1, numLen = 0, numStr[5], lastSpacingPos = -1, numSpacingDiff, numLastSpacingDiff, numSpacingDiffCount // -225\0 (4 len)
	;
	while(i <= len)
	{
		lastCh = ch;
		ch = szStr[i];
		switch(ch)
		{
			case '0'..'9':
			{
				if(numIsValid) {
					if(lastCh == '-') {
						if(numLen == 0 && ignoreNegatives == false) {
							isNumNegative = true;
						}
						else if(numLen > 0) {
							numIsValid = false;
						}
					}
					if(numLen == (3 + _:isNumNegative)) { // IP Num is valid up to 4 characters.. -255
						for(numLen = 3; numLen > 0; numLen--) {
							numStr[numLen] = EOS;
						}
					}
					else if(lastCh == '-' && ignoreNegatives) {
						i++;
						continue;
					} else {
						if(numLen == 0 && numIsValid == true && isNumNegative == true && lastCh == '-') {
							numStr[numLen++] = lastCh;
						}
						numStr[numLen++] = ch;
					}
				}
			}
			default: // skip non +/-0-255
			{
				if(numLen && numIsValid) {
					numberFound = strval(numStr);
					if(numberFound >= -255 && numberFound <= 255) {
						if(fixedSeparation) {
							if(lastSpacingPos != -1) {
								numLastSpacingDiff = numSpacingDiff;
								numSpacingDiff = i - lastSpacingPos - numLen;
								if(trueIPInts == 1 || numSpacingDiff == numLastSpacingDiff) {
									++numSpacingDiffCount;
								}
							}
							lastSpacingPos = i;
						}
						if(++trueIPInts >= 4) {
							break;
						}
					}
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
	if(fixedSeparation == true && numSpacingDiffCount < 3) {
		return 0;
	}
	return (trueIPInts >= 4);
}