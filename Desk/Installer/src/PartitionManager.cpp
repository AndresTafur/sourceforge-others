#include <parted/parted.h>

class PartitionManager
{
public:


	PartitionManager()
	{

	    PedDevice* device;
	    PedDisk* disk;
	    PedPartition* part = NULL;


		ped_device_probe_all();

	  	device 	   = ped_device_get_next(NULL);
	   	disk 	   = ped_disk_new (device);
		partitions = ped_disk_get_max_primary_partition_count(disk);
		list 	   = (PedPartition**) malloc( sizeof(PedPartition)*(partitions+3));

		

		for(i=0; (part = ped_disk_next_partition (disk, part));)
		{
			if( part )
		   	   if(part->type ==  PED_PARTITION_NORMAL || part->type ==  PED_PARTITION_LOGICAL)
		   	   {
				list[i] = part;
				i++;
	           	   }
		}

	}


	int HowManyPartitions()
	{
		return i;
	}


	int GetNumOf(int index)
	{
		return	list[index]->num;
	}


	const char* GetTypeOf(int index)
	{
		return list[index]->fs_type->name;
	}


protected:
int i;
PedPartition** list;
int partitions;
};
