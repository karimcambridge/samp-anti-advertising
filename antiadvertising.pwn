#include <a_samp>

stringContainsIP(const szStr[])
{
	new 
		iDots, iColons, i = 0, trueIPInts = 0,
		numberFound = -1, numLen = 0, numStr[4]
	;
	while(szStr[i] != EOS)
	{
		if('0' <= szStr[i] <= '9')
		{
			while(('0' <= szStr[i] <= '9') || szStr[i] == '.' || szStr[i] == ':' || szStr[i] == '_' || szStr[i] == ' ')
			{
				switch(szStr[i])
				{
					case '0'..'9':
					{
						if(numLen == 3) {
							numLen = 0;
						} else {
							numStr[numLen++] = szStr[i];
						}
					}
					case '.', '_': iDots++;
					case ':': iColons++;
					case ' ': i++; // skip whitespaces
				}
				if(!('0' <= szStr[i] <= '9') && numLen) {
					numberFound = strval(numStr);
					if(numberFound >= 0 && numberFound <= 255) {
						trueIPInts++;
					}
					for(numLen = 3; numLen > 0; numLen--) { // strdel(numStr, 0, 3); // numStr[numLen] = EOS; ... they just won't work d:
						numStr[numLen] = EOS;
					} // numLen goes back to 0!
				}
				i++;
			}
		}
		if(iDots >= 3 && iColons == 1 && trueIPInts >= 4) {
			return 1;
		} else {
			iDots = 0;
			numLen = 0;
			numStr[numLen] = EOS;
			numberFound = -1;
		}
		i++;
	}
	return 0;
}

main() {}

public OnGameModeInit()
{
	new str[64];
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
	str = "0000.000.000.0000:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "255.256.255.255:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	str = "-1.-1.-1.-1:7777";
	printf("%s - %d.", str, stringContainsIP(str));
	return 1;
}