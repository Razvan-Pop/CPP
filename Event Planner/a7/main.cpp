#include "Ui.h"
#include "RepositoryExceptions.h"
#include "CSVEventList.h"
#include "HTMLEventList.h"
#include <fstream>

using namespace std;

int main() {

	try {
		ofstream file("Events.txt", ios::out | ios::trunc);
		Repository repository("Events.txt");
		repository.generateEvents();
		FileEventList* p = nullptr;
		cout << "What type of file would you like to use to store the eventList (CSV/HTML)?";
		string fileType{};
		cin >> fileType;
		if (fileType == "CSV")
			p = new CSVEventList{ "eventlist.csv" };
		else
			p = new HTMLEventList{ "eventlist.html" };
		Controller controller{ repository, p, EventValidator{} };
		Ui ui(controller);
		ui.run();
		delete p;
	}

	catch(FileException&){
		cout << "Repository file could not be opened! The application will terminate." << endl;
		return 1;
	}

	return 0;
}