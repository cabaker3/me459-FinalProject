import pandas as pd
from datetime import datetime as dt

def mamt(df):
    day_oamt_dict = pd.DataFrame()
    ranges = list(zip(df['started_date_x'], df['completed_date_x']))
    range2 = list(merge_ranges(ranges))
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
    
#def excel_date(date1):
#    temp = dt.datetime(1899, 12, 30)    
#    delta = date1 - temp
#    return float(delta.days) + (float(delta.seconds) / 86400)
    
def Application(oamt):
    #Clean data - get rid of any null values for task code
    tasks=pd.DataFrame(oamt)
    tasks=tasks.dropna(subset=['task_code'],how='any')
    
    #Reformat Date Columns
    tasks['started_date_x'] = pd.to_datetime(tasks['started_date_x'],format='%Y-%m-%d %H:%M:%S')
    tasks['completed_date_x'] = pd.to_datetime(tasks['completed_date_x'],format='%Y-%m-%d %H:%M:%S')
    
    #Clean up data - removing any duplicates
    raw_data = {'task_code': tasks['task_code'], 'oamt_barcode': tasks['oamt_barcode']}
    raw_data.drop_duplicates(subset=['oamt_barcode', 'task_code'], keep='first', inplace=True)
    
    #Perform MAMT calculations
    temp = tasks.groupby('oamt_barcode').apply(mamt)
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