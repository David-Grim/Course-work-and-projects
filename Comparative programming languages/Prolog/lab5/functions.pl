% David Grim
% dgrim@ucsc.edu


% Prolog not
not(X) :- X, !, fail.
not(_).

% from haversine.lis.pdf 
haversine(Lat1, Lon1, Lat2, Lon2, D) :-
   Dlon is Lon2 - Lon1,
   Dlat is Lat2 - Lat1,
   A is (sin(Dlat/2)) ** 2 + cos(Lat1)
      * cos(Lat2) * (sin( Dlon/2 )) ** 2,
   C is 2 * atan2(sqrt(A), sqrt(1 - A)),
   D is 3961 * C.
   
% convert degrees to radians
deg_to_rad(degmin(Degrees, Minutes), Rad) :-
   Deg is Degrees + Minutes / 60,
   Rad is (Deg * pi) / 180.

 
distance(Airport1, Airport2, D) :-
   airport(Airport1, _, Lat1, Lon1),
   airport(Airport2, _, Lat2, Lon2),
   deg_to_rad(Lon1, Lon1rad),
   deg_to_rad(Lat1, Lat1rad),
   deg_to_rad(Lon2, Lon2rad),
   deg_to_rad(Lat2, Lat2rad),
   haversine(Lat1rad, Lon1rad, Lat2rad, Lon2rad, D).

% conversion to just hours
just_hours(time(Hours, Mins), FHours) :-
   FHours is Hours + Mins / 60.

% assuming flight is constantly flying at 500MPH
% convert miles to hours
miles_to_hours(Miles, Hours) :-
   Hours is Miles / 500.


% correctly format how the time is displayed
print_digits(Digits) :-
   Digits >= 10,
   print(Digits).

print_digits(Digits) :-
   Digits < 10, 
   print(0), print(Digits).

% print current time
print_time(FHours) :-
   Totalmin is floor(FHours * 60),
   Hours is Totalmin // 60,
   Mins is Totalmin mod 60,
   print_digits(Hours),
   print(:),
   print_digits(Mins).

% find the path
findpath(ArrivingTerminal, ArrivingTerminal, _, [ArrivingTerminal], _). 

findpath(DepartingTerminal, ArrivingTerminal, VisitedList, 
   [[DepartingTerminal, Depart, Arrive] | List], Departure) :-
   flight(DepartingTerminal, ArrivingTerminal, Departure),
   not(member(ArrivingTerminal, VisitedList)),
   distance(DepartingTerminal, ArrivingTerminal, Dist),
   miles_to_hours(Dist, TravelTime),
   just_hours(Departure, Depart),
   Arrive is Depart + TravelTime,
   Arrive < 24.0, % flight cannot be > 24 hours
   findpath(ArrivingTerminal, ArrivingTerminal, 
      [ArrivingTerminal | VisitedList], List, _).

% find the next path
findpath(DepartingTerminal, ArrivingTerminal, VisitedList,
   [[DepartingTerminal, Depart, Arrive] | List], Departure) :-
   flight(DepartingTerminal, NextTerminal, Departure),
   not(member(NextTerminal, VisitedList)),
   distance(DepartingTerminal, NextTerminal, Dist),
   miles_to_hours(Dist, TravelTime),
   just_hours(Departure, Depart),
   Arrive is Depart + TravelTime,
   Arrive < 24.0, % flight cannot be > 24 hours
   flight(NextTerminal, _, ConnectingHM),
   just_hours(ConnectingHM, ConnectingTime),
   (Arrive + 0.5) =< ConnectingTime, % 30 minute layover
   findpath( NextTerminal, ArrivingTerminal,
      [NextTerminal | VisitedList], List, ConnectingHM).

printpath([[First, FirstD, FirstA], Second | []]) :-
   airport(First, FirstName, _, _), airport(Second, SecondName, _, _),
   write('      '), write('Depart:    '), write(First), write('  '),
   write(FirstName), write('     '), print_time(FirstD), nl, nl,
   write('      '), write('Arrive:    '), write(Second), write('  '),
   write(SecondName), write('     '), print_time(FirstA), nl,nl.

printpath([[First, FirstD, FirstA], 
          [Second, SecondD, SecondA] | Tail]) :-
   airport(First, FirstName, _, _), airport( Second, SecondName, _, _),
   write('      '), write('Depart:    '), write(First), write('  '),
   write(FirstName), write('     '), print_time(FirstD), nl, nl,
   write('      '), write('Arrive:    '), write(Second), write('  '),
   write(SecondName), write('     '), print_time(FirstA), nl, nl,
   printpath([[Second, SecondD, SecondA] | Tail]).

% case for flying to the same airport.
fly(Beginning, Beginning) :-
   write('*ERROR*: Starting and destination '),
   write('terminal were the same!'),
   nl, !, fail.

% case for a valid flight.
fly(Beginning, Destination) :-
   airport(Beginning, _, _, _),
   airport(Destination, _, _, _),
   findpath(Beginning, Destination, [Beginning], List, _),
   !, nl, printpath(List), true.

% case for when the airport does exist but flight does not 
fly(Beginning, Destination) :-
   airport(Beginning, _, _, _),
   airport(Destination, _, _, _),
   write('*ERROR*: The flight '),
   write(Beginning), write(' to '),
   write(Destination),
   write(' does not exist '),
   write('or flight is longer than 24 hours!'), nl,
   !, fail.

% case for if the flight is invalid
fly(_, _) :-
   write('*ERROR*: invalid flight.'), nl,
   !, fail.
