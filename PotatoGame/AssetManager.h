#if !defined(PG_ASSET_MANAGER_H)
#define PG_ASSET_MANAGER_H

#include "PGList.h"
#include "PGBaseObjectList.h"
#include "PGFont.h"
#include "PGTexture.h"
#include "PGGameModel.h"

using namespace PG::Core;
namespace PG {
	namespace Engine {

		class AssetManager {
		protected:

		private:
			bool IsFontLoadingEnable;
			FT_Library* Ft_lib_Intance;

			PGBaseObjList<PGFont>* Fonts_List;
			PGBaseObjList<RawModelData>* Obj_Model_List;
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
			AssetManager() {
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

				this->Obj_Model_List = new PGBaseObjList<RawModelData>(true);
			}
			~AssetManager() {
				delete(this->Fonts_List);
				delete(this->Textures_List);
				delete(this->Obj_Model_List);

				//Note(Marc):Free the freetype lib after we free the font list
				FT_Done_FreeType(*this->Ft_lib_Intance);

				FreeImage_DeInitialise();

			}
			PGFont* AssetManager::LoadFont(char *path, char* ref_Name) {
				if (IsFontLoadingEnable == true) {
					PGFont* new_font = new PGFont(this->Ft_lib_Intance, path, ref_Name);
					new_font->Build();
					this->Fonts_List->Add(new_font);

					return new_font;
				}
				return nullptr;
			}
			PGTexture*  AssetManager::LoadTexture(PGTexFormat format, char *path, char* ref_Name) {
				PGTexture* new_texture = new PGTexture(format, path, ref_Name);
				new_texture->Build();
				this->Textures_List->Add(new_texture);
				return new_texture;
			}
			PGTexture* AssetManager::SeachForTexture(char* ref_Texture_Name) {
				return Textures_List->FindByName(ref_Texture_Name);
			}
			PGFont* AssetManager::SeachForFont(char* ref_Font_Name) {
				return Fonts_List->FindByName(ref_Font_Name);
			}
		};
	}
}
#endif