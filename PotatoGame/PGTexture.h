#if !defined(PG_TEXTURE_H)
#define PG_TEXTURE_H



#include "stdafx.h"
 
#include "PGString.h"
#include "PGBaseObject.h"
#include "PGBuildableObject.h"

using namespace PG::Core;

namespace PG {
	namespace Engine {
		enum PGTexFormat {
			PG_PNG = 0,
			PG_BMP = 1
		};
		class PGTexture : public PGBaseObject, PGBuildableObject {
		protected:
		private:
			GLuint GenGlTex(FIBITMAP *bitmap) {
				GLuint new_tex_id = 0;
				if (bitmap != nullptr) {
					FIBITMAP *converted_bitmap = FreeImage_ConvertTo32Bits(bitmap);
					if (converted_bitmap != nullptr) {
						int nWidth = FreeImage_GetWidth(converted_bitmap);
						int nHeight = FreeImage_GetHeight(converted_bitmap);

						glGenTextures(1, &new_tex_id);
						glBindTexture(GL_TEXTURE_2D, new_tex_id); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object		

						// Set the texture wrapping parameters
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

						// Set texture filtering parameters
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(converted_bitmap));
						glGenerateMipmap(GL_TEXTURE_2D);//note(marc):don't know if we should create mipmap everytime?
					}
					else {
						//Todo(marc):add debug stream
					}
					FreeImage_Unload(converted_bitmap);
				}
				else {
					//Todo(marc):add debug stream
				}
				return new_tex_id;
			}
		public:
			PGTexFormat Format;
			Str *File_Path;
			GLuint OpenGL_Id;

			PGTexture(PGTexFormat format, char* file_path, char * texture_ref_name)
				:PGBaseObject() {
				this->Set_Name(texture_ref_name);
				this->Format = format;
				this->File_Path = new Str(file_path);
			}
			~PGTexture() {
				glDeleteTextures(1, &OpenGL_Id);
				delete(File_Path);
			}
			void PGTexture::Build() override {
				PGBuildableObject::StartBuilding();
				switch (this->Format) {
				case PG_PNG:{
								this->OpenGL_Id = GenGlTex(FreeImage_Load(FIF_PNG, File_Path->CharAt(), 0));
								break;
				}
				case PG_BMP:{
								this->OpenGL_Id = GenGlTex(FreeImage_Load(FIF_BMP, File_Path->CharAt(), 0));
								break; }
				default:
					break;
				}
				PGBuildableObject::EndBuilding();
			}
		};
	}
}
#endif