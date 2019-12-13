// דנאפ נאחבטעûי םא ןמהדנאפû
class Components
{
public:
	Components(int n);
	int Find(int u);
	void Merge(int x, int y);
private:
	int* parents, * ranks;
	int n;
};