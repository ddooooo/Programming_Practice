import heapq

def solution(k, n, reqs):
    left = n-k
    counsellor = []
    for i in range(k):
        counsellor.append(1)
    
    reqs_rearrange = []
    for i in range(k):
        new = []
        for req in reqs:
            if req[2] == i+1:
                new.append([req[0],req[1]])
        reqs_rearrange.append(new)

    while left>=0:
        answer = 0
        max_delay = -1
        assign = 0
        for i in range (k):
            print(f"Session {i+1}")
            finish_times = []
            total_delay = 0
            num_counsellor = counsellor[i]
            for req in reqs_rearrange[i]:
                if num_counsellor>0:
                    num_counsellor -= 1
                    finish_time = req[0]+req[1]
                    heapq.heappush(finish_times, finish_time)
                    print(f"Start time : {req[0]} ~ Finish time : {finish_time}")
                else:
                    start_time = heapq.heappop(finish_times)
                    finish_time = start_time+req[1]    
                    delay = start_time-req[0]
                    if delay < 0:
                        print(f"Available mentor exists!!")
                        delay = 0

                    total_delay += delay
                    heapq.heappush(finish_times, finish_time)
                    print(f"Start time : {start_time} ~ Finish time : {finish_time} -> waiting time : {total_delay}")

            print(f"Total delay: {total_delay}")
            answer += total_delay
            if total_delay > max_delay:
                max_delay = total_delay
                assign = i
        
        if answer == 0:
            break
        
        counsellor[assign] += 1
        left -=1
        for c in counsellor:
            print(f" counsellor : {c}")
    

    return answer

def main():
    reqs = [[0, 60, 1], [20, 100, 1], [30, 50, 3], [60, 100, 2], [70, 100, 2], [80, 30, 1], [100, 30, 2], [120, 100, 1], [125, 100, 4], [135, 100, 5]]
    # reqs = [[10, 60, 1], [15, 100, 1], [20, 30, 1], [30, 50, 1], [50, 40, 1], [60, 30, 3], [65, 30, 1], [70, 100, 1]]
    # reqs = [ [10, 80, 1], [25, 30, 2], [50, 30, 2], [70, 20, 1], [95, 100, 1]  ]
    # reqs = [[10, 60, 1], [15, 100, 3], [20, 30, 1], [30, 50, 3], [50, 40, 1], [60, 30, 2], [65, 30, 1], [70, 100, 2]]
    # reqs = [[5, 55, 2], [10, 90, 2], [20, 40, 2], [50, 45, 2], [100, 50, 2]]
    # answer = solution(2, 3, reqs)
    answer = solution(5, 6, reqs)
    print(f"answer : {answer}")

if __name__ == "__main__":
    main()