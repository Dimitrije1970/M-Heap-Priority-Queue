#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include "heap.h"
#include "priority_queue.h"

using namespace std;

void performance_analysis() {
	int index = 0;

	chrono::duration<double, std::milli> insertion_times[12];
	int insertion_steps[12];

	chrono::duration<double, std::milli> deletion_times[12];
	int deletion_steps[12];

	Heap* heap = nullptr;

	for (int i = 100; i <= 100000; i *= 10) {
		string input_file_name = "test_";
		input_file_name += to_string(static_cast<int>(i));
		input_file_name += ".txt";

		ifstream input_file;
		input_file.open(input_file_name);
		if (!input_file.is_open()) break;
		string line;

		for (int j = 2; j <= 8; j *= 2) {
			heap = new Heap(j);
			int steps = 0;
			input_file.clear();
			input_file.seekg(0);

			auto start = chrono::high_resolution_clock::now();

			while (getline(input_file, line)) {
				heap->add(stoi(line), steps);
			}

			auto end = chrono::high_resolution_clock::now();

			insertion_times[index] = end - start;
			insertion_steps[index] = steps;

			steps = 0;

			start = chrono::high_resolution_clock::now();

			while (!heap->is_empty()) {
				heap->remove(0, steps);
			}

			end = chrono::high_resolution_clock::now();

			deletion_times[index] = end - start;
			deletion_steps[index++] = steps;
		}

		delete heap;
	}

	cout << endl;

	int cnt_size = 10, cnt_m = 2;

	for (int i = 0; i < 12;i++) {
		if (i % 3 == 0) cnt_size *= 10, cnt_m = 2;

		cout << setw(6) << setfill(' ') << cnt_size << ", " << cnt_m << "   "
			<< setw(8) << setfill(' ') << fixed << setprecision(4) << insertion_times[i].count() << "   "
			<< setw(7) << setfill(' ') << insertion_steps[i] << "   "
			<< setw(8) << setfill(' ') << fixed << setprecision(4) << deletion_times[i].count() << "   "
			<< setw(7) << setfill(' ') << deletion_steps[i] << endl;

		cnt_m *= 2;
	}

	cout << endl;
}


int main() {

	int first_choice = -1;

	Heap* h1 = nullptr;
	PriorityQueue* pq = nullptr;

	while (1) {
		if (first_choice == 1) {
			cout << endl;

			int m;
			cout << "Unesi red heapa: "; cin >> m;

			h1 = new Heap(m);

			cout << "Heap uspesno kreiran." << endl << endl;

		}
		else if (first_choice == 2) {
			int k, min, max, steps = 0;

			cout << endl << "Unesi broj elemenata: ";
			cin >> k;

			cout << "Min Max: ";
			cin >> min >> max;

			int i;
			for (i = 0; i < k; i++) {
				int random_int = min + (rand() % (max - min));
				h1->add(random_int, steps);
			}

		}
		else if (first_choice == 3) {
			cout << endl;

			cout << "1. test_10.txt" << endl;
			cout << "2. test_100.txt" << endl;
			cout << "3. test_1000.txt" << endl;
			cout << "4. test_10000.txt" << endl;
			cout << "5. test_100000.txt" << endl;
			cout << "Unesi redni broj fajla: ";
			int second_choice; cin >> second_choice;

			if (second_choice < 1 || second_choice > 5) break;
			string input_file_name = "test_";
			input_file_name += to_string(static_cast<int>(pow(10, second_choice)));
			input_file_name += ".txt";

			ifstream input_file;
			input_file.open(input_file_name);
			if (!input_file.is_open()) break;

			int steps = 0;
			string line;

			while (getline(input_file, line)) {
				h1->add(stoi(line), steps);
			}

			cout << "Dodavanje uspesno zavrseno." << endl << endl;

		}
		else if (first_choice == 4) {
			cout << endl;

			int element, steps = 0;
			cout << "Unesi element: "; cin >> element;

			h1->add(element, steps);

			cout << "Element uspesno dodat." << endl << endl;

		}
		else if (first_choice == 5) {
			cout << endl;

			cout << h1->get();

			cout << endl << endl;

		}
		else if (first_choice == 6) {
			cout << endl;

			int steps = 0;

			h1->remove(0, steps);

			cout << "Element uspesno obrisan." << endl << endl;

		}
		else if (first_choice == 7) {
			cout << endl;

			int steps = 0;

			int to_remove;
			cout << "Unesi element za brisanje: "; cin >> to_remove;

			int to_remove_index = -1;
			if(h1)to_remove_index = h1->find_index(to_remove);

			int code = h1->remove(to_remove_index, steps);

			if(code != -1) cout << "Element uspesno obrisan." << endl << endl;

		}
		else if (first_choice == 8) {
			int steps = 0;

			cout << endl << "Unesi novo m: ";
			int new_m; cin >> new_m;

			Heap* new_heap = new Heap(new_m);

			while (!h1->is_empty()) new_heap->add(h1->remove(0, steps), steps);

			delete h1;
			h1 = new_heap;

			cout << "Heap sa redom " << h1->get_m() << " uspesno kreiran." << endl << endl;

		}
		else if (first_choice == 9) {
			int steps = 0, steps_merge = 0;

			Heap* h2 = new Heap(h1->get_m());
			h2->add(2, steps);
			h2->add(25, steps);
			h2->add(17, steps);
			h2->add(48, steps);
			h2->add(4, steps);
			h2->add(70, steps);
			h2->add(110, steps);

			if(h1) h1 = merge(*h1, *h2, steps_merge);

			cout << endl << "Heapovi uspesno spojeni." << endl << endl;

			delete h2;

		}
		else if (first_choice == 10) {
			cout << endl;

			if (h1) cout << *h1;

			cout << endl << endl;

		}
		else if (first_choice == 11) {
			cout << endl;

			delete h1;

			cout << "Heap uspesno obrisan." << endl << endl;

		}
		else if (first_choice == 12) {
			cout << endl;

			pq = new PriorityQueue();

			cout << "Prioritetni red uspesno kreiran." << endl << endl;

		}
		else if (first_choice == 13) {
			if (pq && !pq->is_empty()) {
				cout << endl << "Prioritetni red nije prazan." << endl << endl;
			}
			else {
				cout << endl << "Prioritetni red je prazan." << endl << endl;
			}

		}
		else if (first_choice == 14) {
			cout << endl;

			if (pq) cout << pq->front();

			cout << endl << endl;

		}
		else if (first_choice == 15) {
			cout << endl;

			int element, steps = 0;
			cout << "Unesi element: "; cin >> element;

			pq->insert(element);

			cout << "Element uspesno dodat." << endl << endl;

		}
		else if (first_choice == 16) {
			cout << endl;

			pq->remove();

			cout << "Element uspesno obrisan." << endl << endl;

		}
		else if (first_choice == 17) {
			cout << endl;

			delete pq;

			cout << "Heap uspesno obrisan." << endl << endl;

		}
		else if (first_choice == 18) {
			performance_analysis();

		}else if (first_choice == 0) {
			break;

		}

		cout << "--- Heap ---" << endl << endl;
		cout << "1. Kreiraj heap." << endl;
		cout << "2. Dodaj nasumicno generisane elemente." << endl;
		cout << "3. Dodaj elemente iz fajla." << endl;
		cout << "4. Dodaj jedan element." << endl;
		cout << "5. Dohvati minimalni element." << endl;
		cout << "6. Obrisi minimalni element." << endl;
		cout << "7. Obrisi proizvoljan element." << endl;
		cout << "8. Pretvori heap u heap novog reda." << endl;
		cout << "9. Spoji heapove." << endl;
		cout << "10. Ispisi heap u obliku m-arnog stabla." << endl;
		cout << "11. Obrisi heap." << endl << endl;
		
		cout << "--- Prioritetni red ---" << endl << endl;
		cout << "12. Kreiraj prioritetni red." << endl;
		cout << "13. Ispitaj popunjenost." << endl;
		cout << "14. Dohvati prvi element." << endl;
		cout << "15. Dodaj element." << endl;
		cout << "16. Izbaci element." << endl;
		cout << "17. Obrisi prioritetni red." << endl << endl;

		cout << "18. Analiza performansi." << endl << endl;

		cout << "0. Prekini program." << endl;
		cout << "Unesi redni broj opcije: ";
		cin >> first_choice;

	}

	return 0;
}