#if !defined(PG_FONT_H)
#define PG_FONT_H

#include "stdafx.h"

#include "PGString.h"
#include "PGBaseObject.h"
#include "PGBuildableObject.h"

using namespace PGCore;

namespace PGEngine {
	
	#define TOG_Font_Loaded_Character_Cpt 128
	
	struct PGCharacter {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	class PGFont : public PGBaseObject , PGBuildableObject{
			bool IsErrorWithFace;
			FT_Face Ft_face;
		public:
			PGCharacter CharacterCollection[128];
			PGFont(FT_Library *ft_lib, char* file_path, char* font_name )
				:PGBaseObject(){
					this->Set_Name(font_name);
					this->IsErrorWithFace = true;
					this->IsErrorWithFace = FT_New_Face(*ft_lib, file_path, 0, &this->Ft_face);
				
			}
			~PGFont() {
				FT_Done_Face(this->Ft_face);
				for (GLubyte c = 0; c < TOG_Font_Loaded_Character_Cpt; c++) {
					glDeleteTextures(1, &this->CharacterCollection[c].TextureID);
				}
			}			
			void  PGFont::Build() override{
				PGBuildableObject::StartBuilding();
				if (this->IsErrorWithFace == false) {

					//FT_Set_Pixel_Sizes(this->Ft_face, 0, 48);
					FT_Set_Pixel_Sizes(this->Ft_face, 0, 48);
					glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

					for (GLubyte c = 0; c < TOG_Font_Loaded_Character_Cpt; c++) {
						// Load character glyph 
						if (FT_Load_Char(this->Ft_face, c, FT_LOAD_RENDER)) {
							continue;
						}
						// Generate texture
						GLuint texture_ref_id;
						glGenTextures(1, &texture_ref_id);
						glBindTexture(GL_TEXTURE_2D, texture_ref_id);
						
						// Set texture options
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
						// Set texture filtering parameters
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

						glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
							this->Ft_face->glyph->bitmap.width,
							this->Ft_face->glyph->bitmap.rows,
							0,
							GL_RED, GL_UNSIGNED_BYTE,
							this->Ft_face->glyph->bitmap.buffer
							);
						//glGenerateMipmap(GL_TEXTURE_2D);
						// Now store character for later use
						this->CharacterCollection[c] = { texture_ref_id,
							glm::ivec2(this->Ft_face->glyph->bitmap.width, this->Ft_face->glyph->bitmap.rows),
							glm::ivec2(this->Ft_face->glyph->bitmap_left, this->Ft_face->glyph->bitmap_top),
							this->Ft_face->glyph->advance.x
						};
					}
				}
				PGBuildableObject::EndBuilding();
			}
			void PGFont::GetFontBondingBox(char* text_in, r32 scale_in, v2 *box_out) {
				
			}	
	};
}

#endif