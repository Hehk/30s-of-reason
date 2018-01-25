type t = {
  port: int,
  algoliaApplicationId: string,
  algoliaAPIKey: string
};

let getEnvVar = key => {
  switch (key |> Js.Dict.get(Node.Process.process##env)) {
  | None => ""
  | Some(x) => x
  };
};
let env = {
  port: 3000,
  algoliaApplicationId: getEnvVar("ALGOLIA_APPLICATION_ID"),
  algoliaAPIKey: getEnvVar("ALGOLIA_API_KEY")
};
