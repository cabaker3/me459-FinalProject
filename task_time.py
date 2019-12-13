import pandas as pd
from datetime import datetime as dt
import timeit

def mamt(df):
    day_oamt_dict = pd.DataFrame()
    ranges = list(zip(df['Started_Date_x'], df['Completed_Date_x']))
    start_time = timeit.default_timer()
    range2 = list(merge_ranges(ranges))
    elapsed = (timeit.default_timer() - start_time) * 1000
    print(elapsed)
    val = []
    for a, b in range2:
        diff = b - a
        days, seconds = diff.days, diff.seconds
        hours = diff.total_seconds()/3600
        val.append(hours)

    return sum(val)

def merge_ranges(ranges):
    ranges = iter(sorted(ranges))
    current_start, current_stop = next(ranges)
    for start, stop in ranges:
        if start > current_stop:
            # Gap between segments: output current segment and start a new one.
            yield current_start, current_stop
            current_start, current_stop = start, stop
        else:
            # Segments adjacent or overlapping: merge.
            current_stop = max(current_stop, stop)
    yield current_start, current_stop
    
def Application(oamt):
    #Clean data - get rid of any null values for task code
    tasks=pd.DataFrame(oamt)
    tasks=tasks.dropna(subset=['task_code'],how='any')
    
    #Reformat Date Columns
    tasks['Started_Date_x'] = pd.to_datetime(tasks['Started_Date_x'],format='%Y-%m-%d %H:%M:%S')
    tasks['Completed_Date_x'] = pd.to_datetime(tasks['Completed_Date_x'],format='%Y-%m-%d %H:%M:%S')
    
    #Clean up data - removing any duplicates
    raw_data = {'task_code': tasks['task_code'], 'oamt_barcode': tasks['oamt_barcode']}
    t = pd.DataFrame(raw_data)
    t.drop_duplicates(subset=['oamt_barcode', 'task_code'], keep='first', inplace=True)
    
    #Perform MAMT calculations
    start_time = timeit.default_timer()
    temp = tasks.groupby('oamt_barcode').apply(mamt)
    elapsed = (timeit.default_timer() - start_time) * 1000
    print(elapsed)
    s = pd.Series(temp,index=temp.index)
    
    #Sum task times based on business rules
    temp2 = pd.DataFrame({'OAMT_BARCODE':s.index,'MAMT':s.values})
    temp2['Sample_Size'] = temp2['MAMT'].apply(lambda x: 1 if x != 0.0 and x < 16.0 else 0)
    temp3 = pd.merge(temp2,t,left_on='OAMT_BARCODE',right_on='oamt_barcode')
    temp3['MAMT_Sum'] = temp3.apply(lambda x: x['MAMT'] if x['Sample_Size'] == 1 else 0, axis =1)
    
    #Get Average MAMT for task
    s1=temp3.groupby('task_code').sum()
    s1['Task_Code_Average_MAMT'] = s1.apply(lambda x: x['MAMT_Sum'] / x['Sample_Size'] if x['MAMT_Sum'] != 0.0 else 0.0 , axis=1)
    
    s1.to_csv('mamt_output.csv')

#get neccessary input data
df_oamt = pd.read_csv('task_data_py.csv', encoding='ISO-8859-1')

Application(df_oamt)
