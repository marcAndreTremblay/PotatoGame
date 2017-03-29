#if !defined(PG_CORE_H)
#define PG_CORE_H

namespace PG {
	namespace Core {

		#define DEBUGMODE 1  // 1 = true 0 = false
		#if DEBUGMODE
		#endif

		typedef glm::int8 int8;
		typedef glm::int16 int16;
		typedef glm::int32 int32;
		typedef glm::int64 int64;

		typedef glm::uint8 uint8;
		typedef glm::uint16 uint16;
		typedef glm::uint32 uint32;
		typedef glm::uint64 uint64;

		typedef glm::float64 r64;
		typedef glm::float32 r32;

		typedef glm::vec4 v4;
		typedef glm::vec3 v3;
		typedef glm::vec2 v2;

		typedef glm::mat4 m4;
		typedef glm::mat3 m3;
		typedef glm::mat2 m2;


		#define PG_60HZT 0.01666666666f
		#define PG_30HZT 0.03333333333f
		#define PG_Pi32  3.14159265359f



		template <class T>
		class Buffer {
		public:
			T* data;
			int count;
			Buffer(int element_count) {
				data = (T*)malloc(sizeof(T)*element_count);
				count = element_count;
			}
			Buffer() {
				data = nullptr;
				count = 0;
			}
			~Buffer() {
				free(data);
			}
			T* Buffer::At(int i) {
				return &data[i];
			}
		};
	}
}
#endif