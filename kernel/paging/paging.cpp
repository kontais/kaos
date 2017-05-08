struct PML4
{
	unsigned int address : 20;
	unsigned int unused : 3;
	bool G : 1;
	bool pageSize : 1;
	bool zero : 1;
	bool accessed : 1;
	bool cacheDisable : 1;
	bool writeThrough : 1;
	bool user : 1;
	bool writeable : 1;
	bool present : 1;
};

struct PDE
{
	unsigned int address : 20;
	unsigned int unused : 3;
	bool G : 1;
	bool pageSize : 1;
	bool zero : 1;
	bool accessed : 1;
	bool cacheDisable : 1;
	bool writeThrough : 1;
	bool user : 1;
	bool writeable : 1;
	bool present : 1;
};

struct PTE
{
	unsigned int address : 20;
	unsigned int unused : 3;
	bool global : 1;
	bool zero : 1;
	bool dirty : 1;
	bool accessed : 1;
	bool cacheDisable : 1;
	bool writeThrough : 1;
	bool user : 1;
	bool writeable : 1;
	bool present : 1;
};

