void GetList(int cla_number, int stu_number, string& id, string& name)
{
	int number;
	string Sid, Sname;
	if (cla_number == 1)
	{
		ifstream fin("1������.txt");
		while (fin >> number >> Sid >> Sname)
		{
			if (number == stu_number)
			{
				id = Sid;
				name = Sname;
				break;
			}
		}
	}
	else if (cla_number == 2)
	{
		ifstream fin("1��ʵ��.txt");
		while (fin >> number >> Sid >> Sname)
		{
			if (number == stu_number)
			{
				id = Sid;
				name = Sname;
				break;
			}
		}
	}
	else if (cla_number == 3)
	{
		ifstream fin("2������.txt");
		while (fin >> number >> Sid >> Sname)
		{
			if (number == stu_number)
			{
				id = Sid;
				name = Sname;
				break;
			}
		}
	}
	else if (cla_number == 4)
	{
		ifstream fin("2��ʵ��.txt");
		while (fin >> number >> Sid >> Sname)
		{
			if (number == stu_number)
			{
				id = Sid;
				name = Sname;
				break;
			}
		}
	}
	else if (cla_number == 5)
	{
		ifstream fin("15��1��.txt");
		while (fin >> number >> Sid >> Sname)
		{
			if (number == stu_number)
			{
				id = Sid;
				name = Sname;
				break;
			}
		}
	}
	else if (cla_number == 6)
	{
		ifstream fin("15��2��.txt");
		while (fin >> number >> Sid >> Sname)
		{
			if (number == stu_number)
			{
				id = Sid;
				name = Sname;
				break;
			}
		}
	}
}