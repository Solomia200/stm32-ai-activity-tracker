enum Activity {
  stationary('Stationary'),
  walking('Walking'),
  jogging('Joggging'),
  stairs('Stairs'),
  unknown('❓ Unknown');

  final String label;
  const Activity(this.label);
}
