type t = {
  .
  "id": int,
  "content": string,
  "description": string,
  "example": string,
  "jsOutput": string,
  "objectID": string
};


let graphQLType = "
  type Snippet {
    id: ID! @unique
    content: String!
    description: String!
    example: String!
    jsOutput: String!
  }";

let workingReDir = "./snippets/";
let workingJsDir = "./lib/js/snippets/";

let listSnippetNames = () => {
  Node.Fs.readdirSync(workingReDir)
  |> Array.map(name => String.sub(name, 0, String.length(name) - 3));
};

let loadSnippetRawRe = name => {
  Node.Fs.readFileAsUtf8Sync(workingReDir ++ name ++ ".re")
};

let loadSnippetJsOutput = name => {
  Node.Fs.readFileAsUtf8Sync(workingJsDir ++ name ++ ".bs.js");
};

let createSnippet = (~id, ~rawRe, ~jsOutput, ~name, ()) => {
  let pattern = [%bs.re "/(\\/\\* @description )([\\s\\S]*)(\\*\\/)([\\s\\S]*)(\\/\\* @content \\*\\/)([\\s\\S]*)(\\/\\* @example \\*\\/)([\\s\\S]*)/"];
  /* God i hate regex in Reason */
  let segments = switch (Js.Re.exec(rawRe, pattern)) {
  | None => [||];
  | Some(result) => result
    |> Js.Re.captures
    |> Array.map(Js.Nullable.to_opt)
    |> Array.map(segment => switch segment {
      | None => ""
      | Some(x) => x
    })
  };
  switch segments {
  | [| _all, _descHeader, description, _descEnd, _setup, _contentHeader, content, _exampleHeader, example |] => {
      "id": id,
      "description": String.trim(description),
      "content": String.trim(content),
      "example": String.trim(example),
      "jsOutput": jsOutput,
      "objectID": name
    }
  | _ => { "id": -1, "description": "", "content": "", "example": "", "jsOutput": "", "objectID": name }
  };
};

let loadSnippets = () => {
  listSnippetNames()
  |> Array.mapi((i, name) => createSnippet(
    ~id=i,
    ~rawRe=loadSnippetRawRe(name),
    ~jsOutput=loadSnippetJsOutput(name),
    ~name=name,
    ()))
  |> Array.to_list
  |> List.filter(snippet => snippet##id === -1 ? false : true)
  |> Array.of_list
};

module Store {
  let algoliaClient = Algolia.make(
    ~applicationId=Config.env.algoliaApplicationId,
    ~apiKey=Config.env.algoliaAPIKey,
    ()
  );
  let algoliaIndex = Algolia.Index.make("30s-snippets", algoliaClient); 
  let local = loadSnippets();

  Algolia.Index.addObjects(
    local,
    algoliaIndex
  );
  
  let getByQuery = (query) => {
    let res = Algolia.Index.search({ "query": query }, algoliaIndex);
    res
    |> Js.Promise.then_((x: {. "hits": array(t)}) => Js.Promise.resolve(x##hits));
  }
};

module Handler {
  type graphQLContext;

  type resolvers('root) = {
    queries: {.
      "allSnippets": (Js.Nullable.t('root), {. "query": Js.Nullable.t(string)}, Js.t(graphQLContext)) => 
        Js.Promise.t(array(t))
    },
  };

  let make = () => {
    queries: {
      "allSnippets": (_root, input, _context) => {
        switch (Js.Nullable.to_opt(input##query)) {
        | Some(query) => Store.getByQuery(query)
        | None => Js.Promise.resolve([||])
        }
      }
    }
  }
};
