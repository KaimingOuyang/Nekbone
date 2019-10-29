#include <stdio.h>
#include <unistd.h>

void sample_process_and_task_(){
	int i;
	const int cores = 36;
	long long timestep = 0;
	int *priv_shm_idle_process;
	int *priv_shm_avail_tasks;
	int total_idle_process;
	int total_avail_tasks;

	MPI_Get_stealing_profile_data(&priv_shm_idle_process, &priv_shm_avail_tasks);

	FILE *fp = fopen("timestep.log","w");
	do{
		total_avail_tasks = total_idle_process = 0;
		for(i=0;i<cores;++i){
			total_idle_process += priv_shm_idle_process[i];
			total_avail_tasks += priv_shm_avail_tasks[i];
		}
		fprintf(fp, "%lld %d %d\n", timestep, total_idle_process, total_avail_tasks);
		usleep(100);
		timestep += 100;
	} while(1);
	return;
}