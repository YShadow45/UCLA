#include<string>
#include<iostream>
#include<cctype>
#include<cassert>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
bool readForecast(string text, int& pos);
bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);
int processForecast(string text, char party);

int main()
{
	int seats = -999;
	assert(tallySeats("", 'd', seats) == 0 && seats == 0);
	seats = -999;
	assert(tallySeats("c", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("cA", 'd', seats) == 0 && seats == 0);
	seats = -999;
	assert(tallySeats("DN", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("ma111D", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("maD", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("ma4@", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("vt14D6R9I", 'd', seats) == 0 && seats == 14);
	seats = -999;
	assert(tallySeats("vt14D6R9I,", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("ca11D2R,Ma8R4I", 'd', seats) == 0 && seats == 11);
	seats = -999;
	assert(tallySeats("ca11D2R,Ma,vT2e5d6r", 'd', seats) == 0 && seats == 16);
	seats = -999;
	assert(tallySeats("ZT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '@', seats) == 2 && seats == -999);
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 22);
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'r', seats) == 0 && seats == 12);
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'i', seats) == 0 && seats == 1);
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'c', seats) == 0 && seats == 0);
	cout << "All tests succeeded!" << endl;
}

bool isValidUppercaseStateCode(string stateCode)  //to verify a valid state code
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

bool readForecast(string text, int& pos1)  //to combine the number and party as a unit and verify their validity
{
	string num = "";
	while (isdigit(text[pos1]))  //Accept following digits
	{
		num += text[pos1];
		pos1++;
	}
	if (num.size() > 2)  //make sure no more than 2
		return false;
	if (!isalpha(text[pos1]))  //party character must follow the forecast
		return false;
	return true;
}

bool hasProperSyntax(string pollData)
{
	if (pollData == "")  //the empty string is valid
		return true;
	for (int k = 0; k != pollData.size(); k++)  //convert to upper case 
	{
		pollData[k] = toupper(pollData[k]);
	}
	
	int pos = 0;  //create a cursor
	while (pos < pollData.size())  //read through the string
	{
		if (!isValidUppercaseStateCode(pollData.substr(pos, 2)))  //state code at the beginning
			return false;
		pos += 2;
		if (!(pos < pollData.size()))
			continue;
		while (true)  //2 choices after state code: ',' or a digit. If ',', execute the loop again; if digit, call the function to verify.
		{
			switch (pollData[pos])
			{
			case ',':
				if (pos + 1 == pollData.size())
					return false;
				else
					pos++;
				break;
			default:
				if (!isdigit(pollData[pos]))
					return false;
				else if (!readForecast(pollData, pos))
					return false;
				pos++;
				if (pos == pollData.size())
					break;
				continue;
			}
			break;
		}
	}
	return true;
}

int tallySeats(string pollData, char party, int& seatTally)
{
	if (!hasProperSyntax(pollData))
		return 1;
	if (!isalpha(party))
		return 2;
	seatTally = processForecast(pollData, party);
	return 0;
}

int processForecast(string text, char party)  //calculate the forecast
{
	int count = 0, pos = 0;
	for (int i = 0; i < text.size(); i++)
		if (toupper(text[i + 1]) == toupper(party) && isdigit(text[i]))
		{
			pos = i + 1;
			if (isdigit(text[i - 1]))
				count += (text[i - 1] - '0') * 10 + text[i] - '0';
			else
				count += text[i] - '0';
		}
	return count;
}