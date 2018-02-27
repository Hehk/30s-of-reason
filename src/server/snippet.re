type t = {
  .
  "id": string,
  "title": string,
  "content": string,
  "description": string,
  "example": string,
  "jsOutput": string,
  "objectID": string,
  "section": string,
  "typeSpec": string
};

let graphQLType = {|
  type Snippet {
    id:          ID! @unique
    title:       String!
    content:     String!
    description: String!
    example:     String!
    jsOutput:    String!
    section:     String!
    typeSpec:    String!
  }
|};

module Scraper = {
  let workingReDir = "./snippets/";
  let workingJsDir = "./lib/js/snippets/";
  let listSnippetNames = () =>
    Node.Fs.readdirSync(workingReDir)
    |> Array.map(name => String.sub(name, 0, String.length(name) - 3));
  let loadSnippetRawRe = name =>
    Node.Fs.readFileAsUtf8Sync(workingReDir ++ name ++ ".re");
  let loadSnippetJsOutput = name =>
    Node.Fs.readFileAsUtf8Sync(workingJsDir ++ name ++ ".bs.js");
  let createSnippet = (~id, ~rawRe, ~jsOutput, ~name, ()) => {
    let pattern =
      Js.Re.fromString(
        "(\\/\\* @title )([\\s\\S]*)(\\*\\/[\\s\\S]*)"
        ++ "(\\/\\* @section )([\\s\\S]*)(\\*\\/[\\s\\S]*)"
        ++ "(\\/\\* @description )([\\s\\S]*)(\\*\\/[\\s\\S]*)"
        ++ "(\\/\\* @type )([\\s\\S]*)(\\*\\/[\\s\\S]*)"
        ++ "(\\/\\* @content \\*\\/)([\\s\\S]*)"
        ++ "(\\/\\* @example \\*\\/)([\\s\\S]*)"
      );
    /* God i hate regex in Reason */
    let segments =
      switch (Js.Re.exec(rawRe, pattern)) {
      | None => [||]
      | Some(result) =>
        result
        |> Js.Re.captures
        |> Array.map(Js.Nullable.to_opt)
        |> Array.map(segment =>
             switch segment {
             | None => ""
             | Some(x) => x
             }
           )
      };
    switch segments {
    | [|
        _all,
        _titleHeader,
        title,
        _titleEnd,
        _sectionHeader,
        section,
        _sectionEnd,
        _descHeader,
        description,
        _descEnd,
        _typeHeader,
        typeSpec,
        _typeEnd,
        _contentHeader,
        content,
        _exampleHeader,
        example
      |] => {
        "id": id,
        "title": String.trim(title),
        "description": String.trim(description),
        "typeSpec": String.trim(typeSpec),
        "section": String.trim(section),
        "content": String.trim(content),
        "example": String.trim(example),
        "jsOutput": jsOutput,
        "objectID": name
      }
    | _ => {
        "id": "",
        "description": "",
        "title": "",
        "content": "",
        "example": "",
        "jsOutput": "",
        "section": "",
        "typeSpec": "",
        "objectID": name
      }
    };
  };
  let loadSnippets = () =>
    listSnippetNames()
    |> Array.mapi((i, name) =>
         createSnippet(
           ~id={j|$(i)-$(name)|j},
           ~rawRe=loadSnippetRawRe(name),
           ~jsOutput=loadSnippetJsOutput(name),
           ~name,
           ()
         )
       )
    |> Array.to_list
    |> List.filter(snippet => snippet##id === "" ? false : true)
    |> Array.of_list;
};

module Store = {
  let algoliaClient =
    Algolia.Client.make(
      ~applicationId=Config.env.algoliaApplicationId,
      ~apiKey=Config.env.algoliaAPIKey,
      ()
    );
  let algoliaIndex = Algolia.Index.make("30s-snippets", algoliaClient);
  let local = Scraper.loadSnippets();
  Algolia.Index.addObjects(local, algoliaIndex);
  let getByQuery = query =>
    algoliaIndex
    |> Algolia.Index.search({"query": query})
    |> Js.Promise.then_(x => Js.Promise.resolve(x##hits));
  let getById = id =>
    local
    |> Array.to_list
    |> List.filter(snippet => snippet##id == id)
    |> List.hd;
};

module Handler = {
  type graphQLContext;
  type resolvers('root) = {
    queries: {
      .
      "allSnippets":
        (
          Js.Nullable.t('root),
          {. "query": Js.Nullable.t(string)},
          Js.t(graphQLContext)
        ) =>
        Js.Promise.t(array(t)),
      "snippet":
        (Js.Nullable.t('root), {. "id": string}, Js.t(graphQLContext)) => t
    }
  };
  let make = () => {
    queries: {
      "allSnippets": (_root, input, _context) =>
        switch (Js.Nullable.to_opt(input##query)) {
        | Some(query) => Store.getByQuery(query)
        | None => Js.Promise.resolve([||])
        },
      "snippet": (_root, input, _context) => Store.getById(input##id)
    }
  };
};
