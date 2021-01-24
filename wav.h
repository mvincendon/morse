#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include "config.h"

#include "Correspondance/corres.h"

using std::vector;
using std::string;
using std::endl;
using std::fstream;



typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4] = {'R','I','F','F'};        // RIFF Header Magic header
    uint32_t        ChunkSize;// = fsize + 36;          // RIFF Chunk Size
    uint8_t         WAVE[4] = {'W','A','V','E'};        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4] = {'f','m','t',' '};         // FMT header
    uint32_t        Subchunk1Size = 16;                 // Size of the fmt chunk
    uint16_t        AudioFormat = 1;                    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan = 1;                      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec = 44100;              // Sampling Frequency in Hz
    uint32_t        bytesPerSec = 44100*2;              // bytes per second
    uint16_t        blockAlign = 2;                     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample = 8;                  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
    uint32_t        Subchunk2Size;                      // Sampled data length
} wav_hdr;

class Wav{

    protected:
        wav_hdr _header;
        vector<double> _data;
        long unsigned int fluct;
        Correspondance* _corres;

        double sous_mediane(const long unsigned int debut, const long unsigned int fin) const;

        void convertir(char &car);

        void generer(const unsigned short int nbUnits, const bool silence);

        bool ecoute(const double val, const bool silence) const;

        int periode(const long unsigned int debut, const bool silence) const;

        string lire_fichier(const string source);

        string interpreter() const;

    public:
        Wav(const string corres){
            _corres = new Correspondance(corres);
        }

        void ecrire(string texte, const string target);

        void ecrire_fichier(const string source, const string target);

        string lire(const string source);
};

