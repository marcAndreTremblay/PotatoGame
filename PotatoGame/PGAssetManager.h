#if !defined(PG_ASSET_MANAGER_H)
#define PG_ASSET_MANAGER_H

#include "PGList.h"
#include "PGBaseObjectList.h"
#include "PGFont.h"
#include "PGTexture.h"

using namespace PGCore;


namespace PGEngine {
	class PGRawObjFile : PGBaseObject, PGBuildableObject {
	protected:
		PGLList<v3>* Vertices;
		PGLList<v2>* UVs;
		PGLList<v3>* Normals;
	private:
		PGString *File_Path;
	public:
		PGRawObjFile(char* REF_NAME,char* FILE_PATH) : PGBaseObject() {
			this->Set_Name(REF_NAME);
			this->File_Path = new PGString(FILE_PATH);


			Vertices = new PGLList<v3>(true);
			UVs = new PGLList<v2>(true);
			Normals = new PGLList<v3>(true);
		}
		~PGRawObjFile() {
			delete(File_Path);

			delete(Vertices);
			delete(UVs);
			delete(Normals);
		}
		void PGRawObjFile::Build() override {
			PGBuildableObject::StartBuilding();
			
			//v3 v_tab[100];
			//int v_c_index = 0;

			//v3 vn_tab[100];
			//int vn_c_index = 0;

			//v2 vt_tab[100];
			//int vt_c_index = 0;
			//
			//
			//FILE * file = fopen("Asset/RawOBJ/test_cube.obj", "r");
			//if (file != nullptr) {
			//	char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
			//	while (1) {
			//		int res = fscanf(file, "%s", lineHeader);
			//		//	printf("Read String1 |%s|\n", lineHeader);                                                   
			//		if (res == EOF) {
			//			break; // EOF = End Of File. Quit the loop.
			//		}
			//		if (strcmp(lineHeader, "v") == 0) {
			//			int match_cpt = fscanf_s(file, "%f %f %f\n", &v_tab[v_c_index].x, &v_tab[v_c_index].y, &v_tab[v_c_index].z);
			//			if (match_cpt != 3) {
			//				printf("Error reading vertices tangent Num:|%i|\n", v_c_index);
			//			}
			//			v_c_index++;
			//		}
			//		else if (strcmp(lineHeader, "vn") == 0) {
			//			int match_cpt = fscanf_s(file, "%f %f %f\n", &vn_tab[vn_c_index].x, &vn_tab[vn_c_index].y, &vn_tab[vn_c_index].z);
			//			if (match_cpt != 3) {
			//				printf("Error reading vertices tangent Num:|%i|\n", vn_c_index);
			//			}
			//			vn_c_index++;
			//		}
			//		else if (strcmp(lineHeader, "vt") == 0) {
			//			int match_cpt = fscanf_s(file, "%f %f\n", &vt_tab[vt_c_index].x, &vt_tab[vt_c_index].y);
			//			if (match_cpt != 2) {
			//				printf("Error reading Tex coords Num:|%i|\n", vt_c_index);
			//			}
			//			vt_c_index++;
			//		}
			//		else if (strcmp(lineHeader, "f") == 0) {
			//			unsigned int face_data[9] = {};
			//			int match_cpt = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",  &face_data[0], &face_data[1], &face_data[2],
			//														&face_data[3], &face_data[4], &face_data[5], 
			//														&face_data[6], &face_data[7], &face_data[8]);
			//			if (match_cpt != 9) {
			//				printf("Error reading face data\n");
			//			}
			//		}	
			//		else if (strcmp(lineHeader, "usemtl") == 0) {
			//		
			//		}
			//		else if (strcmp(lineHeader, "s") == 0) {
			//		
			//		}

			//	}
			//}
			//while (v_c_index >= 1) {
			//	printf("Verticles : %f %f %f\n", v_tab[v_c_index].x, v_tab[v_c_index].y, v_tab[v_c_index].z);
			//	v_c_index--;
			//}
			//while (vn_c_index >= 1) {
			//	printf("Normal  : %f %f %f\n", vn_tab[vn_c_index].x, vn_tab[vn_c_index].y, vn_tab[vn_c_index].z);
			//	vn_c_index--;
			//}
			//while (vt_c_index >= 1) {
			//	printf("V tex : %f %f\n", vt_tab[vt_c_index].x, vt_tab[vt_c_index].y);
			//	vt_c_index--;
			//}


			PGBuildableObject::EndBuilding();
		}
	};

	class PGAssetManager {
		protected:

		private:
			bool IsFontLoadingEnable;			
			FT_Library* Ft_lib_Intance;
			
			PGBaseObjList<PGFont>* Fonts_List;
			PGBaseObjList<PGRawObjFile>* Obj_Model_List;
			PGBaseObjList<PGTexture>* Textures_List;
 
			static void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
				//Todo(Marc):Log error
				printf("\n*** ");
				if (fif != FIF_UNKNOWN) {
					printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
				}
				printf(message);
				printf(" ***\n");
			}
		public:
			PGAssetManager() {
				this->IsFontLoadingEnable = false;

				/* Init Texture loading */
				this->Textures_List = new PGBaseObjList<PGTexture>(true);
				FreeImage_Initialise(false);
				FreeImage_SetOutputMessage(FreeImageErrorHandler);


				/* Init Font loading */
				this->Fonts_List = new PGBaseObjList<PGFont>(true);
				this->Ft_lib_Intance = new FT_Library();
				FT_Error result_error = FT_Init_FreeType(this->Ft_lib_Intance);
				if (result_error != false) {
					//Todo(Marc):Log error
				}
				else {
					this->IsFontLoadingEnable = true;
				}

				this->Obj_Model_List = new PGBaseObjList<PGRawObjFile>(true);
			}
			~PGAssetManager() {
				delete(this->Fonts_List);
				delete(this->Textures_List);
				delete(this->Obj_Model_List);

				//Note(Marc):Free the freetype lib after we free the font list
				FT_Done_FreeType(*this->Ft_lib_Intance);

				FreeImage_DeInitialise();

			}
			PGFont* PGAssetManager::LoadFont(char *path, char* ref_Name) {
				if (IsFontLoadingEnable == true) {
					PGFont* new_font = new PGFont(this->Ft_lib_Intance, path, ref_Name);
					new_font->Build();
					this->Fonts_List->Add(new_font);

					return new_font;
				}
				return nullptr;
			}
			PGTexture*  PGAssetManager::LoadTexture(PGTexFormat format, char *path, char* ref_Name) {
				PGTexture* new_texture = new PGTexture(format, path, ref_Name);
				new_texture->Build();
				this->Textures_List->Add(new_texture);
				return new_texture;
			}
			PGTexture* PGAssetManager::SeachForTexture(char* ref_Texture_Name) {
				return Textures_List->FindByName(ref_Texture_Name);
			}
			PGFont* PGAssetManager::SeachForFont(char* ref_Font_Name) {
				return Fonts_List->FindByName(ref_Font_Name);
			}
	};
}
#endif