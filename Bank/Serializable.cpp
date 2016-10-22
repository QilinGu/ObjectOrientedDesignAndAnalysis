/**
* Created by: Pearson Radu
* The Serializable class saves or loads a vector of one of the three types of members.
* Simply just puts the data in a text file.
* Previously I did have a method that would use actual object serialization to save the data.
* Unfortunately I was unable to unserialize the data properly, or I would have to resort to boost serialization.
*/

#include "stdafx.h"
#include "Serializable.h"

void Serializable::saveTime(ofstream& fileWriter, tm time)
{
	// Save the seconds
	fileWriter << time.tm_sec << "\n";
	// Save the minutes
	fileWriter << time.tm_min << "\n";
	// Save the hours
	fileWriter << time.tm_hour << "\n";
	// Save the day
	fileWriter << time.tm_mday << "\n";
	// Save the month
	fileWriter << time.tm_mon << "\n";
	// Save the year
	fileWriter << time.tm_year << "\n";
}

Serializable::Serializable()
{
}

Serializable::~Serializable()
{
}

/**
 * \brief
 * Save Trace Function
 * This function takes a vector of strings, as well as a size and bool and writes it to a file
 * \param traces
 * \param toggle
 */
void Serializable::saveTrace(vector<string>& traces, bool toggle)
{
	ofstream fileWriter("traces.pr");

	if (fileWriter.is_open())
	{
		// Save the toggle (which tells us if the traces we on or off last)
		fileWriter << toggle << "\n";
		// Save the number of traces, so we know how many to search for when we load them back
		fileWriter << traces.size() << "\n";

		// Save the individual trace
		for (size_t i = 0; i < traces.size(); i++)
			fileWriter << traces[i] << "\n";
	}

	fileWriter.close();
}

/**
 * \brief
 * Load Trace Function
 * This function reads strings from a file and saves it to a vector
 * It returns a boolean to show the if the trace was on or off previously
 * \param traces
 * \return
 */
bool Serializable::loadTrace(vector<string> &traces)
{
	ifstream fileReader("traces.pr");
	string line;

	// Check to see if the toggle was left on or off
	getline(fileReader, line);
	bool toggle = true;
	if (line == "0")
		toggle = false;

	// Check to see how many traces were left
	getline(fileReader, line);
	int numTrace = stoi(line);

	// Load the individual traces
	for (int i = 0; i < numTrace; i++)
	{
		getline(fileReader, line);
		traces.push_back(line);
		getline(fileReader, line);
	}

	fileReader.close();

	return toggle;
}
