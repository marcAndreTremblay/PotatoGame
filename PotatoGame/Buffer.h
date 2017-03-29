#if !defined(PG_BUFFER_H)
#define PG_BUFFER_H

namespace PG {
	namespace Core {
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