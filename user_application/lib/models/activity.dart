enum Activity {
  stationary('Resting'),
  walking('Walking'),
  jogging('Running'),
  climbingdown('Climbingdown'),
  climbingup("Climbingup"),
  unknown('❓ Unknown');

  // 0: "walking",
//     1: "running",
//     2: "climbingdown",
//     3: "climbingup",
//     4: "resting"
  final String label;
  const Activity(this.label);
}
