#if !defined(PG_STRING_H)
#define PG_STRING_H

#include "stdafx.h"

namespace PGCore {

	//Todo(Marc): Add overloading operator and cancatenation
	//Todo(Marc): Split the file into .h and .ccp
	//Todo(Marc): Remove the window dependancie by implementing the string compare and string lenght
	//Todo(Marc): Remove the \n at the end we doont need it, and it created problem for file loading
	//But still a think if you want to create string without the lenght specification, so maybe add a contructor
	class PGString {
	protected:
	private:
		char *text_ptr; //poiter to the start of the string in memory
		int char_count; //Char count without the end marker
	public:
		PGString() {
			this->char_count = 0;
			this->text_ptr = nullptr;

		}
		PGString(char *text_string, int max_string_lenght = 100) {
			//Count the char
			int char_cpt = 0;
			char *tempo_str = text_string;
			while (*tempo_str != '\n') {
				char_cpt++;
				tempo_str++;
			}
			char_count = char_cpt;

				//Get the memory from Windows
				this->text_ptr = (char*)malloc(sizeof(char)*this->char_count + 1);

				//Copy to dest string
				tempo_str = text_string;
				char* dest_str = this->text_ptr;
				while (*tempo_str != '\n') {
					*dest_str = *tempo_str;
					dest_str++;
					tempo_str++;
				}
				*dest_str = '\n';
			
		}
		~PGString() {
			free(this->text_ptr);
		}
		char* PGString::GetCharPtr() {
			return text_ptr;
		}
		bool PGString::Compare_Ptr(PGString* other) {
			return (this == (void*)other);
		}
		bool PGString::Compare(PGString* other) {
			if (this->char_count != other->char_count) return false;
			char* current_char = this->text_ptr;
			char* current_other_char = other->text_ptr;
			bool CurrentCharAlike = true;
			while (CurrentCharAlike) {
				if (*current_char != *current_other_char) {
					return false;
				}
				else {
					if (*current_char == '\n') {
						return true;
					}
					current_char++;
					current_other_char++;
				}
			}
			return false;
		}
		PGString* PGString::Append(char *new_text) {
			//Count the new string char count
			int char_cpt = 0;
			char *tempo_str = new_text;
			while (*tempo_str != '\n') {
				char_cpt++;
				tempo_str++;
			}

			//Set new compined char count
			this->char_count += char_cpt;

			//Ask for memory
			char *new_str = (char*)malloc(this->char_count + 1);

			//Copy old string first
			tempo_str = this->text_ptr;
			char* dest_str = new_str;
			while (*tempo_str != '\n') {
				*dest_str = *tempo_str;
				dest_str++;
				tempo_str++;
			}
			//Copy new string second
			tempo_str = new_text;
			while (*tempo_str != '\n') {
				*dest_str = *tempo_str;
				dest_str++;
				tempo_str++;
			}

			//Add end masker at the end of both
			*dest_str = '\n';

			//Free old one
			free(this->text_ptr);

			//Set new  ptr to data
			this->text_ptr = new_str;

			return this;
		}
	
};
}
#endif	