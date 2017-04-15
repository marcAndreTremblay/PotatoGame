#if !defined(PG_STRING_H)
#define PG_STRING_H

#include "stdafx.h"


#define ENDSTR '\0'

namespace PG {
	namespace Core {
		class Str {
		protected:
		private:
		public:
			char *data_ptr;
			int char_count;
			Str(int s_char) {
				char_count = s_char + 1;
				this->data_ptr = (char*)malloc(sizeof(char)*this->char_count);
				this->data_ptr[char_count] = ENDSTR;
			}
			Str(char *text) {
				//Count the char
				int char_cpt = 1; //Add one for the end string char
				char *tempo_str = text;
				while (*tempo_str != ENDSTR) {
					char_cpt++;
					tempo_str++;
				}
				char_count = char_cpt;

				//Get the memory from Windows
				this->data_ptr = (char*)malloc(sizeof(char)*this->char_count);

				//Copy to dest string
				tempo_str = text;
				char* dest_str = this->data_ptr;
				while (*tempo_str != ENDSTR) {
					*dest_str = *tempo_str;
					dest_str++;
					tempo_str++;
				}
				*dest_str = ENDSTR;
			}
			~Str() {
				free(data_ptr);
			}
			bool Str::Compare(Str* other) {
				if (this->char_count != other->char_count) return false;
				char* current_char = this->data_ptr;
				char* current_other_char = other->data_ptr;
				bool CurrentCharAlike = true;
				while (CurrentCharAlike) {
					if (*current_char != *current_other_char) {
						return false;
					}
					else {
						if (*current_char == ENDSTR) {
							return true;
						}
						current_char++;
						current_other_char++;
					}
				}
				return false;
			}
			Str* Str::Append(char *new_text) {
				//Count the new string char count
				int char_cpt = 0;
				char *tempo_str = new_text;
				while (*tempo_str != ENDSTR) {
					char_cpt++;
					tempo_str++;
				}

				//Set new compined char count
				this->char_count += char_cpt;

				//Ask for memory
				char *new_str = (char*)malloc(this->char_count);

				//Copy old string first
				tempo_str = this->data_ptr;
				char* dest_str = new_str;
				while (*tempo_str != ENDSTR) {
					*dest_str = *tempo_str;
					dest_str++;
					tempo_str++;
				}
				//Copy new string second
				tempo_str = new_text;
				while (*tempo_str != ENDSTR) {
					*dest_str = *tempo_str;
					dest_str++;
					tempo_str++;
				}

				//Add end masker at the end of both
				*dest_str = ENDSTR;

				//Free old one
				free(this->data_ptr);

				//Set new  ptr to data
				this->data_ptr = new_str;

				return this;
			}
			char* Str::CharAt(int i = 0) {
				return &data_ptr[i];
			}
			static Str* Str::ExtractFolderPath(Str *atlas_path) {
				//Count where the last '/' is.		
				char* cursor = atlas_path->CharAt();
				int char_count = 0;
				bool dotfound = false;
				while (true) {
					if (dotfound == false) {
						if (*cursor == 46) {
							dotfound = true;
						}
						else {
							cursor++;
							char_count += 1;
						}
					}
					else {
						if (*cursor == 47) {
							cursor++;
							char_count += 1;
							break;
						}
						else {
							cursor--;
							char_count -= 1;
						}


					}

				}
				Str * new_String = new Str(char_count);
				char* dst_buffer = new_String->CharAt();
				strncpy(dst_buffer, atlas_path->CharAt(), char_count);
				dst_buffer[char_count] = ENDSTR;
				return new_String;
			}
		};
	}
}
#endif	