let types = Snippet.graphQLType;

let query = {|
    type Query {
      allSnippets(query: String): [Snippet]!
      snippet(id: ID!): Snippet!
    }
  |};

let resolvers = {
  let snippet = Snippet.Handler.make();
  {"Query": Js.Obj.empty() |> Js.Obj.assign(snippet.queries)};
};

let schema = {"typeDefs": types ++ query, "resolvers": resolvers};
