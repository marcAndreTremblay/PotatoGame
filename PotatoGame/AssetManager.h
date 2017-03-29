#if !defined(PG_ASSET_MANAGER_H)
#define PG_ASSET_MANAGER_H

#include "List.h"
#include "EngineObjectList.h"
#include "Font.h"
#include "Texture.h"
#include "GameModel.h"

using namespace PG::Core;
namespace PG {
	namespace Engine {

		class AssetManager {
		protected:

		private:
			bool IsFontLoadingEnable;
			FT_Library* Ft_lib_Intance;

			EngineObjectList<Font>* Fonts_List;
			EngineObjectList<RawModelData>* Obj_Model_List;
			EngineObjectList<Texture>* Textures_List;

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
				this->Textures_List = new EngineObjectList<Texture>(true);
				FreeImage_Initialise(false);
				FreeImage_SetOutputMessage(FreeImageErrorHandler);


				/* Init Font loading */
				this->Fonts_List = new EngineObjectList<Font>(true);
				this->Ft_lib_Intance = new FT_Library();
				FT_Error result_error = FT_Init_FreeType(this->Ft_lib_Intance);
				if (result_error != false) {
					//Todo(Marc):Log error
				}
				else {
					this->IsFontLoadingEnable = true;
				}

				this->Obj_Model_List = new EngineObjectList<RawModelData>(true);
			}
			~AssetManager() {
				delete(this->Fonts_List);
				delete(this->Textures_List);
				delete(this->Obj_Model_List);

				//Note(Marc):Free the freetype lib after we free the font list
				FT_Done_FreeType(*this->Ft_lib_Intance);

				FreeImage_DeInitialise();

			}
			Font* AssetManager::LoadFont(char *path, char* ref_Name) {
				if (IsFontLoadingEnable == true) {
					Font* new_font = new Font(this->Ft_lib_Intance, path, ref_Name);
					new_font->Build();
					this->Fonts_List->Add(new_font);

					return new_font;
				}
				return nullptr;
			}
			Texture*  AssetManager::LoadTexture(TextureFormat format, char *path, char* ref_Name) {
				Texture* new_texture = new Texture(format, path, ref_Name);
				new_texture->Build();
				this->Textures_List->Add(new_texture);
				return new_texture;
			}
			Texture* AssetManager::SeachForTexture(char* ref_Texture_Name) {
				return Textures_List->FindByName(ref_Texture_Name);
			}
			Font* AssetManager::SeachForFont(char* ref_Font_Name) {
				return Fonts_List->FindByName(ref_Font_Name);
			}
		};
	}
}
#endif