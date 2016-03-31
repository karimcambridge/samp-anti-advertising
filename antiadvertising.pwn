#include <a_samp>

stringContainsIP(const szStr[])
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
						trueIPInts++;
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

main() {}

public OnGameModeInit()
{
	new str[64];

	// Valid
	str = "000.000.000.000:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "0.0.0.0:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "127.0.0.1:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "127  .  0.  0.  1:  7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "255.255.255.255:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "PLS COME JOIN SERVER 37____187____22____119";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "PLS COME JOIN SERVER 37 $$$$ 187 $$$$ 22 $$$$ 119";
	printf("%s - %d.", str, stringContainsIP(str));

	// Invalid
	str = "0000.000.000.0000:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "255.256.255.255:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "-1.-1.-1.-1:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "1-1.1-1.1-1.1-1:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	return 1;
}