#include "Fasta.h"

void printSummary() {
    cerr << "usage: fastahack <command> [options]" << endl
         << "actions:" << endl 
         << "    index <fasta reference>" << endl
         << "    sequence <fasta reference> <sequence name>" << endl
         << "    subsequence <fasta reference> <sequence name> <0-based start> <length>" << endl
         << "    stats <fasta reference> <sequence name>  (returns sequence length)" << endl;
}

int main (int argc, char** argv) {

    string command;
    string fastaFileName;
    string seqname;
    string longseqname;
    long long start;
    long long length;

    if (!argv[1]) {
        printSummary();
        exit(0);
    } else {
        command = argv[1];
    }

    if (!argv[2]) {
        cerr << "please provide a fasta reference filename" << endl;
        exit(1);
    } else {
        fastaFileName = argv[2];
    }

    if (command == "index") {
        FastaIndex* fai = new FastaIndex();
        cerr << "generating fasta index file from " << fastaFileName << endl;
        fai->indexReference(fastaFileName);
        fai->writeIndexFile((string) fastaFileName + fai->indexFileExtension());
    } else {
        FastaReference* fr = new FastaReference(fastaFileName);
        if (!argv[3]) {
            cerr << "please specify the name of a sequence to print" << endl;
            exit(1);
        } else {
            seqname = argv[3];
        }
        longseqname = fr->sequenceNameStartingWith(seqname);
        if (longseqname == "") {
            cerr << "could not find sequence in reference " << fastaFileName <<
                " named or starting with " << seqname << endl;
            exit(1);
        }

        if (command == "sequence") {
            cout << fr->getSequence(longseqname) << endl;
        } else if (command == "subsequence") {
            if (!argv[4] || !argv[5]) {
                cerr << "no subsequence boundaries specified" << endl;
                exit(1);
            } else {
                char* end;
                start = strtoll(argv[4], &end, 10);
                length = strtoll(argv[5], &end, 10);
            }
            cout << fr->getSubSequence(longseqname, start, length) << endl;
        } else if (command == "stats") {
            cout << fr->sequenceLength(longseqname) << endl;
        }
    }
    return 0;
}
