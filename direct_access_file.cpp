#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;

struct Record {
    int roll_no;
    string name;
    string division;
    string address;
    int chain; // For chaining in without replacement
};

class DirectAccessFile {
private:
    string filename;
    fstream file;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    DirectAccessFile(const string& fname) : filename(fname) {}

    void createDatabase() {
        file.open(filename, ios::out | ios::binary | ios::trunc);
        if (!file) {
            cerr << "Error creating file!" << endl;
            return;
        }
        Record emptyRecord = {-1, "", "", "", -1};
        for (int i = 0; i < TABLE_SIZE; ++i) {
            file.write(reinterpret_cast<const char*>(&emptyRecord), sizeof(Record));
        }
        file.close();
        cout << "Database created successfully." << endl;
    }

    void displayDatabase() {
        file.open(filename, ios::in | ios::binary);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }
        cout << "Roll No\tName\tDivision\tAddress\tChain" << endl;
        Record r;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            file.read(reinterpret_cast<char*>(&r), sizeof(Record));
            if (r.roll_no != -1) {
                cout << r.roll_no << "\t" << r.name << "\t" << r.division << "\t" << r.address << "\t" << r.chain << endl;
            }
        }
        file.close();
    }

    void addRecord(const Record& newRecord, bool withReplacement) {
        file.open(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }

        int hash_address = hashFunction(newRecord.roll_no);
        file.seekg(hash_address * sizeof(Record), ios::beg);
        Record currentRecord;
        file.read(reinterpret_cast<char*>(&currentRecord), sizeof(Record));

        if (currentRecord.roll_no == -1) { // If the slot is empty
            file.seekp(hash_address * sizeof(Record), ios::beg);
            file.write(reinterpret_cast<const char*>(&newRecord), sizeof(Record));
        } else {
            if (withReplacement) {
                // With replacement
                int current_hash = hashFunction(currentRecord.roll_no);
                if (current_hash != hash_address) {
                    // If the current record is not at its home address, replace it
                    file.seekp(hash_address * sizeof(Record), ios::beg);
                    file.write(reinterpret_cast<const char*>(&newRecord), sizeof(Record));
                    addRecord(currentRecord, true); // Re-insert the displaced record
                } else {
                    // Probe for next empty slot
                    linearProbe(hash_address, newRecord, false);
                }
            } else {
                // Without replacement
                linearProbe(hash_address, newRecord, false);
            }
        }
        file.close();
    }

    void linearProbe(int start_address, const Record& newRecord, bool isChain) {
        int current_address = (start_address + 1) % TABLE_SIZE;
        while (current_address != start_address) {
            file.seekg(current_address * sizeof(Record), ios::beg);
            Record temp;
            file.read(reinterpret_cast<char*>(&temp), sizeof(Record));
            if (temp.roll_no == -1) {
                file.seekp(current_address * sizeof(Record), ios::beg);
                file.write(reinterpret_cast<const char*>(&newRecord), sizeof(Record));

                if (!isChain) {
                    // Update chain of the original record
                    int prev_address = start_address;
                    Record prev_rec;
                    while (true) {
                        file.seekg(prev_address * sizeof(Record), ios::beg);
                        file.read(reinterpret_cast<char*>(&prev_rec), sizeof(Record));
                        if (prev_rec.chain == -1) {
                            prev_rec.chain = current_address;
                            file.seekp(prev_address * sizeof(Record), ios::beg);
                            file.write(reinterpret_cast<const char*>(&prev_rec), sizeof(Record));
                            break;
                        }
                        prev_address = prev_rec.chain;
                    }
                }
                return;
            }
            current_address = (current_address + 1) % TABLE_SIZE;
        }
        cout << "Hash table is full. Cannot add record." << endl;
    }


    bool searchRecord(int roll_no) {
        file.open(filename, ios::in | ios::binary);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return false;
        }

        int hash_address = hashFunction(roll_no);
        Record r;

        while (true) {
            file.seekg(hash_address * sizeof(Record), ios::beg);
            file.read(reinterpret_cast<char*>(&r), sizeof(Record));
            if (r.roll_no == roll_no) {
                cout << "Record found:" << endl;
                cout << "Roll No: " << r.roll_no << ", Name: " << r.name << ", Division: " << r.division << ", Address: " << r.address << endl;
                file.close();
                return true;
            }
            if (r.chain == -1) {
                break;
            }
            hash_address = r.chain;
        }

        cout << "Record not found." << endl;
        file.close();
        return false;
    }

    void modifyRecord(int roll_no) {
        if (searchRecord(roll_no)) {
            file.open(filename, ios::in | ios::out | ios::binary);
            if (!file) {
                cerr << "Error opening file!" << endl;
                return;
            }

            int hash_address = hashFunction(roll_no);
             Record r;

            while (true) {
                file.seekg(hash_address * sizeof(Record), ios::beg);
                file.read(reinterpret_cast<char*>(&r), sizeof(Record));
                if (r.roll_no == roll_no) {
                    cout << "Enter new details:" << endl;
                    cout << "Name: ";
                    cin >> r.name;
                    cout << "Division: ";
                    cin >> r.division;
                    cout << "Address: ";
                    cin >> r.address;

                    file.seekp(hash_address * sizeof(Record), ios::beg);
                    file.write(reinterpret_cast<const char*>(&r), sizeof(Record));
                    cout << "Record modified successfully." << endl;
                    break;
                }
                if (r.chain == -1) break;
                hash_address = r.chain;
            }
            file.close();
        }
    }
};

void printMenu() {
    cout << "\n--- Direct Access File Operations ---" << endl;
    cout << "1. Create Database" << endl;
    cout << "2. Display Database" << endl;
    cout << "3. Add a Record" << endl;
    cout << "4. Search a Record" << endl;
    cout << "5. Modify a Record" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    string filename = "student_data.dat";
    DirectAccessFile daf(filename);
    int choice;
    bool withReplacement;

    cout << "Choose hashing method:" << endl;
    cout << "1. Linear Probing without Replacement" << endl;
    cout << "2. Linear Probing with Replacement" << endl;
    int method;
    cin >> method;
    withReplacement = (method == 2);


    do {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                daf.createDatabase();
                break;
            case 2:
                daf.displayDatabase();
                break;
            case 3: {
                Record r;
                cout << "Enter Roll No: ";
                cin >> r.roll_no;
                cout << "Enter Name: ";
                cin >> r.name;
                cout << "Enter Division: ";
                cin >> r.division;
                cout << "Enter Address: ";
                cin >> r.address;
                r.chain = -1;
                daf.addRecord(r, withReplacement);
                break;
            }
            case 4: {
                int roll_no;
                cout << "Enter Roll No to search: ";
                cin >> roll_no;
                daf.searchRecord(roll_no);
                break;
            }
            case 5: {
                int roll_no;
                cout << "Enter Roll No to modify: ";
                cin >> roll_no;
                daf.modifyRecord(roll_no);
                break;
            }
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
