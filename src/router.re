module GraphQL = {
  let snippetStore = Snippet.loadSnippets();
  let types = "type Snippet {
    id: ID! @unique
    content: String!
    description: String!
    example: String!
    jsOutput: String!
  }";
  let query = "type Query { allSnippets: [Snippet]! }";
  let schema = GraphQL.Utilities.buildSchema(types ++ query);
  let rootValue = {
    "allSnippets": () => snippetStore
  };

  let make = () => ApolloServerExpress.createGraphQLExpressMiddleware(schema, ~rootValue)
};
