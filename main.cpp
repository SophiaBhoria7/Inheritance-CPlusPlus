// Simulate genetic inheritance of blood type

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

using namespace std;

// Each child has two parents and two alleles
struct Child {
  shared_ptr<Child> parents[2];
  char alleles[2];
};

const int GENRTN = 3;
const int TABS = 4;

shared_ptr<Child> make_fam(int generations);
void prt_fam(shared_ptr<Child> c, int generation);
char allele_picker();

int main() {
  // Seed random number generator
  srand(time(0));

  // Make a new fam with three generations
  shared_ptr<Child> c = make_fam(GENRTN);

  // Print the fam tree of blood types
  prt_fam(c, 0);

  return 0;
}

// Create a new individual with `generations`
shared_ptr<Child> make_fam(int generations) {
  // Allocate memory for new person
  shared_ptr<Child> p = make_shared<Child>();

  // Generation with parent data
  if (generations > 1) {
    // Recursively create blood type histories for parents
    p->parents[0] = make_fam(generations - 1);
    p->parents[1] = make_fam(generations - 1);

    // Randomly assign child alleles based on parents
    p->alleles[0] = p->parents[0]->alleles[rand() % 2];
    p->alleles[1] = p->parents[1]->alleles[rand() % 2];
  }
  // Generation without parent data
  else {
    // Set parent pointers to NULL
    p->parents[0] = nullptr;
    p->parents[1] = nullptr;

    // Randomly assign alleles
    p->alleles[0] = allele_picker();
    p->alleles[1] = allele_picker();
  }

  // Return newly created person
  return p;
}

// Print each family member and their alleles.
void prt_fam(shared_ptr<Child> c, int generation) {
  // Handle base case
  if (!c) {
    return;
  }

  // Print indentation
  for (int i = 0; i < generation * TABS; i++) {
    cout << " ";
  }

  // Print person
  cout << "Generation " << generation << ", blood type " << c->alleles[0]
       << c->alleles[1] << endl;

  prt_fam(c->parents[0], generation + 1);
  prt_fam(c->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char allele_picker() {
  int allele = rand() % 3;
  if (allele == 0) {
    return 'A';
  } else if (allele == 1) {
    return 'B';
  } else {
    return 'O';
  }
}
