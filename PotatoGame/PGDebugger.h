#if !defined(PG_DEBUGGER_H)
#define PG_DEBUGGER_H



namespace PGCore {
	class PGDebugger {
		static PGDebugger *s_instance;
		PGDebugger() {

		}
	public:
		~PGDebugger() {

		}
		static PGDebugger *instance() {
			if (!s_instance)
				s_instance = new PGDebugger;
			return s_instance;
		}
	};
	PGDebugger *PGDebugger::s_instance = 0;
}
#endif