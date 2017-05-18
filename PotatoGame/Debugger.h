#pragma once
class Debug {
private:
	int id;

public:
	static Debug& Instance();
	void Write(char *message);
	Debug();
	~Debug();
	Debug(Debug const&);              // Don't Implement.
};

