#include "MAVLinkComponent.h"

/* initialise the static data stores */
char MAVLinkComponent::identifiers[MAXIMUM_COMPONENTS][256];
int MAVLinkComponent::systemIDs[MAXIMUM_COMPONENTS];
int MAVLinkComponent::componentIDs[MAXIMUM_COMPONENTS];
long MAVLinkComponent::physicalAddress[MAXIMUM_COMPONENTS][2];
int MAVLinkComponent::numberOfComponents = 0;

/* Constructor, takes a unique identifier
 *	The constructor loads the database if not previously done
 *	it then searches for the passed identifier in that database
 *	if found it sets myComponentNumber to keep track of the data
 *	otherwise it gives an error
 */
MAVLinkComponent::MAVLinkComponent(const char * identifier) {
	if (numberOfComponents == 0) {
		if (loadDatabase() && numberOfComponents == 0) {
			fprintf(stderr,"MAVLinkComponent can't find any components!\n");
			myComponentNumber = -1;
			return;
		}
	}
	
	for (int i = 0; i<numberOfComponents; i++) {
		if (strcmp(identifier,identifiers[i]) == 0) {
			myComponentNumber = i;
			return;
		}
	}
	fprintf(stderr,"MAVLinkComponent can't find '%s'\n", identifier);
	myComponentNumber = -1;
}

/* Return the MAVLink system ID of the component */
int MAVLinkComponent::getSystemID() {
	if (isValidComponent()) {
		return systemIDs[myComponentNumber];
	} else {
		return -1;
	}
}

/* Return the MAVLink component ID of the component */
int MAVLinkComponent::getComponentID() {
	if (isValidComponent()) {
		return componentIDs[myComponentNumber];
	} else {
		return -1;
	}
}

/* Return the high 32-bits of the 64-bit XBee address */
long MAVLinkComponent::getPhysicalAddressHigh() {
	if (isValidComponent()) {
		return physicalAddress[myComponentNumber][0];
	} else {
		return -1;
	}
}

/* Return the low 32-bits of the 64-bit XBee address */
long MAVLinkComponent::getPhysicalAddressLow() {
	if (isValidComponent()) {
		return physicalAddress[myComponentNumber][1];
	} else {
		return -1;
	}
}

/* Load the database */
bool MAVLinkComponent::loadDatabase(const char * filename) {
	/* If we already have components, somethings gone wrong! */
	if (numberOfComponents != 0) {
		fprintf(stderr,"MAVLinkComponent loadDatabase called multiple times!\n");
		return false;
	}

	//open the file
	string line;
	ifstream f(filename);

	//if the file exists, start reading
	if (f.is_open()) {
		//until we reach the end
		while (f.good()) {
			//read a line
			getline(f,line);

			//check whether a line is blank or a comment
			if (isComment(line)) continue;

			//read the parameters
			int count = sscanf(line.c_str(),"%s %d %d %X-%X\n",
				identifiers[numberOfComponents],
				&systemIDs[numberOfComponents],
				&componentIDs[numberOfComponents],
				&physicalAddress[numberOfComponents][0],
				&physicalAddress[numberOfComponents][1]);

			//did we get enough parameters?
			//if yes, increment counter
			//if no, print an error (database is now screwed up)
			//TODO: keep stupid data out of database!
			if (count == 5) {
				numberOfComponents++;
			} else {
				fprintf(stderr, "MAVLinkComponent loadDatabase cannot parse '%s'\n",line.c_str());
			}
		}

		//if we have no components, let the user know
		if (numberOfComponents == 0) {
			fprintf(stderr,"MAVLinkComponent found no components in %s!\n", filename);
			return false;
		}
		//if we have components, tell the user how many
		printf("%d MAVLink Components loaded\n", numberOfComponents);
		return true;
	} else {
		//if the file doesn't exist, tell somebody
		fprintf(stderr,"MAVLinkComponent could not load database!\n");
		numberOfComponents = 0;
	}
	return false;
}

/* Checks if a line is a comment (or blank) */
bool MAVLinkComponent::isComment(string line) {
		bool isComment = false;
		for (int i = 0; i<line.length(); i++) {
			if (line.c_str()[i] != ' ' && line.c_str()[i] != '\t' && line.c_str()[i] == '#') {
				isComment = true;
				break;
			}
			if (line.c_str()[i] != ' ' &&  line.c_str()[i] != '\t') {
				break;
			}
			if (i == line.length()-1) {
				isComment = true;
			}
		}
		if (isComment || line.length() == 0) return true;
		return false;
}

/* Are we a valid component? */
bool MAVLinkComponent::isValidComponent() {
	if (myComponentNumber != -1 && numberOfComponents != 0) {
		return true;
	}
	return false;
}